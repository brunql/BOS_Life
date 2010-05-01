#ifndef HAL_H
#define HAL_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>

//Clock F_CPU == 16000000L

//USART Config
//#define BAUD 9600L
//#include <util/setbaud.h>
//
//#define UBRRL_GET_VALUE 	UBRRL_VALUE
//#define UBRRH_GET_VALUE 	UBRRH_VALUE


#define PRESCALLER				10
#define TiMER_INTERRUPT_VALUE	( F_CPU / PRESCALLER / 1000L )


#define HI(x) ((x) >> 8)
#define LO(x) ((x) & 0x00FF)

#define FALSE 0
#define TRUE -1

extern void InitAll(void);

#endif
