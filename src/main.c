/*
 * main.c
 *
 *  Created on: 23.01.2010
 *      Author: brunql
 */

#include <util/atomic.h>
#include <stdlib.h>

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

void Task_GenerateNewPopulation(void)
{
	ATOMIC_BLOCK( ATOMIC_RESTORESTATE ){
		display_byte_line(0x00, 0);
		generate_next_population();
		OS_AddTaskToTimerQueue( Task_GenerateNewPopulation, POPULATION_DELAY );
	}
}

void Task_UpdateMatrix8x8(void)
{
	ATOMIC_BLOCK( ATOMIC_RESTORESTATE ){
		display_byte_line(population[population_display_index], population_display_index);
		if( ++population_display_index >= 0x08){
			population_display_index = 0x00;
		}
	}
	OS_AddTaskToTimerQueue( Task_UpdateMatrix8x8, UPDATE_MATRIX_DELAY );
}

int main(void)
{
	// Initialize I/O ports and UART if need it
	InitAll();

	// OS initialization: clear timer and eval queue
	OS_Iinialize();

	// Add test tasks
	OS_AddTaskToEvalQueue( Task_UpdateMatrix8x8 );
	OS_AddTaskToTimerQueue( Task_GenerateNewPopulation, POPULATION_DELAY );

	// Configure timers and global enable interrupts
	OS_InitSystemTimerAndSei();

	for(;;){
		// OS takes task from eval queue and run it
		OS_EvalTask();
	}
	return 0;
}

