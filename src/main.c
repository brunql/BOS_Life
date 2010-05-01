/*
 * main.c
 *
 *  Created on: 23.01.2010
 *      Author: brunql
 */

#include <util/atomic.h>
//#include <stdlib.h>

#include "main.h"
#include "matrix8x8.h"
#include "life.h"

#include "bos.h"

uint8_t test = 0x00;

ISR(TiMER_INTERRUPT_VECTOR)
{
	OS_SystemTimerTick();
	SYSTEM_TiMER_COUNTER_RESET_IF_NEED_IT;
}


uint8_t population_display_index = 0x00;

void TaskGenerateNewPopulation(void)
{
	ATOMIC_BLOCK( ATOMIC_RESTORESTATE ){
		display_byte_line(0x00, 0);
		generate_next_population();
		OS_AddTaskToTimerQueue( TaskGenerateNewPopulation, POPULATION_DELAY );
	}
}

void Task_UpdateMatrix8x8(void)
{
	ATOMIC_BLOCK( ATOMIC_RESTORESTATE ){
		display_byte_line(population[population_display_index], population_display_index);
		if( ++population_display_index >= 0x08){
			population_display_index = 0x00;
		}
		OS_AddTaskToEvalQueue( Task_UpdateMatrix8x8 );
	}
	//OS_AddTaskToTimerQueue( Task_UpdateMatrix8x8, UPDATE_MATRIX_DELAY );
}

int main(void)
{
	InitAll();
	OS_Iinialize();

	OS_AddTaskToEvalQueue( Task_UpdateMatrix8x8 );


	OS_AddTaskToTimerQueue( TaskGenerateNewPopulation, POPULATION_DELAY );

	OS_InitSystemTimerAndSei();
//	cli();
	for(;;){
//		wdt_reset();
		OS_EvalTask();
	}
	return 0;
}

