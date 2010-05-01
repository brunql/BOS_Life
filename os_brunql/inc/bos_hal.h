/*
 * bos_hal.h - Brunql real time OS. Headers for hal.
 *
 *  Created on: 23.01.2010
 *      Author: brunql
 */

#ifndef BOS_HAL_H_
#define BOS_HAL_H_

#include <avr/io.h>
#include <avr/interrupt.h> // for sei();
#include "bos.h"

#define TiMER_INTERRUPT_VECTOR	TIMER0_OVF_vect
//#define PRESCALLER				10
//#define TiMER_INTERRUPT_VALUE	( F_CPU / PRESCALLER / 1000L )

#define SYSTEM_TiMER_INIT \
{ \
	TCCR0A = 0x00;	\
	TCCR0B = (0<<CS02) | (1<<CS01) | (0<<CS00);  /* (F_CPU / 256) / 8 == 1ms */ \
	TCNT0 = 0x00; \
}


#define SYSTEM_TiMER_INTERRUPT_ENABLE \
{ \
	TIMSK = _BV( TOIE0 ); \
}

#define SYSTEM_TiMER_COUNTER_RESET_IF_NEED_IT 	{ /* TCNT1 = 0; */ }


void OS_InitSystemTimerAndSei();

#endif /* BOS_HAL_H_ */
