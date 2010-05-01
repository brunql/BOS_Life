/*
 * matrix8x8.h
 *
 *  Created on: 23.01.2010
 *      Author: brunql
 */

#ifndef MATRIX8X8_H_
#define MATRIX8X8_H_

// GREEN
//	    PB0 PB1 PB5 PD1 PB6 PD5 PD4 PB3
//	PB7  *   *   *   *   *   *   *   *
//	PB2  *   *   *   *   *   *   *   *
//	PA0  *   *   *   *   *   *   *   *
//	PB4  *   *   *   *   *   *   *   *
//	PD2  *   *   *   *   *   *   *   *
//	PA1  *   *   *   *   *   *   *   *
//	PD3  *   *   *   *   *   *   *   *
//	PD6  *   *   *   *   *   *   *   *

// columns connected to leds catods
// rows to anods

#define MATRIX_COL_0_ADDR	( &PORTB )
#define MATRIX_COL_0_PIN	( PB0 )
#define MATRIX_COL_1_ADDR	( &PORTB )
#define MATRIX_COL_1_PIN	( PB1 )
#define MATRIX_COL_2_ADDR	( &PORTB )
#define MATRIX_COL_2_PIN	( PB5 )
#define MATRIX_COL_3_ADDR	( &PORTD )
#define MATRIX_COL_3_PIN	( PD1 )
#define MATRIX_COL_4_ADDR	( &PORTB )
#define MATRIX_COL_4_PIN	( PB6 )
#define MATRIX_COL_5_ADDR	( &PORTD )
#define MATRIX_COL_5_PIN	( PD5 )
#define MATRIX_COL_6_ADDR	( &PORTD )
#define MATRIX_COL_6_PIN	( PD4 )
#define MATRIX_COL_7_ADDR	( &PORTB )
#define MATRIX_COL_7_PIN	( PB3 )

#define MATRIX_ROW_0_ADDR	( &PORTB )
#define MATRIX_ROW_0_PIN	( PB7 )
#define MATRIX_ROW_1_ADDR	( &PORTB )
#define MATRIX_ROW_1_PIN	( PB2 )
#define MATRIX_ROW_2_ADDR	( &PORTA )
#define MATRIX_ROW_2_PIN	( PA0 )
#define MATRIX_ROW_3_ADDR	( &PORTB )
#define MATRIX_ROW_3_PIN	( PB4 )
#define MATRIX_ROW_4_ADDR	( &PORTD )
#define MATRIX_ROW_4_PIN	( PD2 )
#define MATRIX_ROW_5_ADDR	( &PORTA )
#define MATRIX_ROW_5_PIN	( PA1 )
#define MATRIX_ROW_6_ADDR	( &PORTD )
#define MATRIX_ROW_6_PIN	( PD3 )
#define MATRIX_ROW_7_ADDR	( &PORTD )
#define MATRIX_ROW_7_PIN	( PD6 )


struct port_addr_pin {
	volatile uint8_t *port_addr;
	uint8_t port_pin;
};

extern struct port_addr_pin matrix_cols[];
extern struct port_addr_pin matrix_rows[];


extern void display_byte(uint8_t showMe);
extern void display_byte_line(uint8_t showMe, uint8_t line);
extern void display_image(uint8_t showMe[8]);

#endif /* MATRIX8X8_H_ */
