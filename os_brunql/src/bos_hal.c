/*
 * bos_hal.c
 *
 *  Created on: 23.01.2010
 *      Author: brunql
 */

#include "bos_hal.h"

void OS_InitSystemTimerAndSei()
{
	SYSTEM_TiMER_INIT;
	SYSTEM_TiMER_INTERRUPT_ENABLE;
	sei();
}
