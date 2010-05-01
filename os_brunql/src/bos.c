/*
 * bos.c - Brunql real time OS. Main file.
 *
 *  Created on: 23.01.2010
 *      Author: brunql
 */
#include <util/atomic.h>
//#include <stdlib.h>
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
	uint8_t next;			// this is index of next task in timerQueue[]
};

//uint8_t timerQueueNowIndex = 0x00;
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
		timerQueue[i].next = 0;
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
		uint8_t now = timerQueue[0].next;
		uint8_t prev = 0x00;
		uint8_t count = 0x00;
		while(timerQueue[now].task != NULL){
			prev = now;
			now = timerQueue[prev].next;
			if( ++count > TIMER_QUEUE_SIZE ){
				OS_Error(TIMER_QUEUE_OVERFLOW);
			}
		}
		if ( now == 0x00 && count == 0x00) {
			now = 1;
		}else if(now == 0x00){
			for(uint8_t i=1; i<TIMER_QUEUE_SIZE; i++){
				if(timerQueue[i].task == NULL){
					now = i;
					break;
				}
			}
			if(now == 0x00){
				OS_Error( TIMER_QUEUE_ADD_ERROR );
			}
		}
		timerQueue[prev].next = now;
		timerQueue[now].task = task;
		timerQueue[now].time_to_eval = time_to_eval;
	}
}

void OS_SystemTimerTick(void)
{
	// now in interrupt
	uint8_t now = timerQueue[0].next;
	uint8_t prev_index = 0x00;
	while(timerQueue[now].task != NULL)
	{
		if( --timerQueue[now].time_to_eval == 0){
			OS_AddTaskToEvalQueue(timerQueue[now].task);
			timerQueue[now].task = NULL; // time == zero
			timerQueue[prev_index].next = timerQueue[now].next;
			timerQueue[now].next = 0x00;
			now = prev_index;	// think about it...
		}
		prev_index = now; // save previous index
		now = timerQueue[now].next; // and update now
	}
}

void OS_EvalTask(void)
{
	ptrTask evalMe = NULL;
	ATOMIC_BLOCK( ATOMIC_RESTORESTATE ){
		if(evalQueue[evalQueueNowIndex] != NULL){
			uint8_t cf = evalQueueNowIndex;
			evalMe = evalQueue[evalQueueNowIndex];
			evalQueue[evalQueueNowIndex] = NULL;
			if( ++evalQueueNowIndex == EVAL_QUEUE_SIZE ){
				evalQueueNowIndex = 0x00;
			}
			evalQueue[cf] = NULL;
			if((evalQueueAddIndex == evalQueueNowIndex) &&
					evalQueue[evalQueueNowIndex]  != NULL ){
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
