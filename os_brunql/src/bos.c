/*
 * bos.c - Brunql real time OS. Main file.
 *
 *  Created on: 23.01.2010
 *      Author: brunql
 */
#include <util/atomic.h>
#include <stdlib.h>
#include "bos.h"

#include "matrix8x8.h"

enum BOS_ERRORS{
	EVAL_QUEUE_OVERFLOW_EVAL_TASK 	= 0x0f << 0,
	EVAL_QUEUE_OVERFLOW_ADD_TASK  	= 0x0f << 1,
	EVAL_QUEUE_ADD_ERROR			= 0x0f << 2,
	TIMER_QUEUE_OVERFLOW			= 0x0f << 3,
	TIMER_QUEUE_ADD_ERROR			= 0x0f << 4
};

struct task {
	ptrTask task;
	uint16_t time_to_eval;
};

struct task timerQueue[ TIMER_QUEUE_SIZE ];

uint8_t evalQueueNowIndex = 0x00;
uint8_t evalQueueAddIndex = 0x00;
ptrTask evalQueue[ EVAL_QUEUE_SIZE ];


void OS_Error(uint8_t error);


void OS_Iinialize(void)
{
	for(uint8_t i=0; i < TIMER_QUEUE_SIZE; i++){
		timerQueue[i].task = NULL;
		timerQueue[i].time_to_eval = 0;
	}

	for(uint8_t i=0; i < EVAL_QUEUE_SIZE; i++){
		evalQueue[i] = NULL;
	}
}

void OS_AddTaskToEvalQueue(ptrTask task)
{
	ATOMIC_BLOCK( ATOMIC_RESTORESTATE ){
		if (evalQueue[evalQueueAddIndex] == NULL){
			evalQueue[evalQueueAddIndex] = task;
			if(++evalQueueAddIndex == EVAL_QUEUE_SIZE){
				evalQueueAddIndex = 0x00;
			}
			if((evalQueueAddIndex == evalQueueNowIndex) &&
					evalQueue[evalQueueAddIndex] != NULL){
				OS_Error(EVAL_QUEUE_OVERFLOW_ADD_TASK);
			}
		}else{
			OS_Error(EVAL_QUEUE_ADD_ERROR);
		}
	}
}

void OS_AddTaskToTimerQueue(ptrTask task, uint16_t time_to_eval)
{
	ATOMIC_BLOCK( ATOMIC_RESTORESTATE ){
		// Было проведено широкомасштабное исследование на клочке бумаги, результат на лицо:
		uint8_t i;
		for(i=0; i < TIMER_QUEUE_SIZE; i++){
			if(timerQueue[i].task == NULL){
				timerQueue[i].task = task;
				timerQueue[i].time_to_eval = time_to_eval;
				break; // !
			}
		}

		if(i == TIMER_QUEUE_SIZE){
			OS_Error(TIMER_QUEUE_OVERFLOW);
		}
	}
}

void OS_SystemTimerTick(void)
{
	// In interrupt from timer
	for(uint8_t i=0; i < TIMER_QUEUE_SIZE; i++){
		if(timerQueue[i].task != NULL){
			if( --timerQueue[i].time_to_eval == 0){
				OS_AddTaskToEvalQueue(timerQueue[i].task);
				timerQueue[i].task = NULL;
				timerQueue[i].time_to_eval = 0;
			}
		}
	}
}

void OS_EvalTask(void)
{
	ptrTask evalMe = NULL;
	ATOMIC_BLOCK( ATOMIC_RESTORESTATE ){
		if(evalQueue[evalQueueNowIndex] != NULL){
			evalMe = evalQueue[evalQueueNowIndex];
			evalQueue[evalQueueNowIndex] = NULL;
			if( ++evalQueueNowIndex == EVAL_QUEUE_SIZE ){
				evalQueueNowIndex = 0x00;
			}
			if((evalQueueAddIndex == evalQueueNowIndex)	&&
					evalQueue[evalQueueNowIndex] != NULL ){
				OS_Error(EVAL_QUEUE_OVERFLOW_EVAL_TASK);
			}
		}// else do nothing, has no tasks
	}
	if(evalMe) (evalMe)();
}

void OS_Error(uint8_t error)
{
	cli();
	// TODO: write here switch on errors and doing something good, before...
	display_byte_line( error, 0 );
	for(;;){ /* error infinity loop */ }
}
