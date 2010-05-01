/*
 * matrix8x8.c
 *
 *  Created on: 23.01.2010
 *      Author: brunql
 */
#include "main.h"
#include "matrix8x8.h"


struct port_addr_pin matrix_cols[8] = {
		{ MATRIX_COL_0_ADDR, _BV( MATRIX_COL_0_PIN ) },
		{ MATRIX_COL_1_ADDR, _BV( MATRIX_COL_1_PIN ) },
		{ MATRIX_COL_2_ADDR, _BV( MATRIX_COL_2_PIN ) },
		{ MATRIX_COL_3_ADDR, _BV( MATRIX_COL_3_PIN ) },
		{ MATRIX_COL_4_ADDR, _BV( MATRIX_COL_4_PIN ) },
		{ MATRIX_COL_5_ADDR, _BV( MATRIX_COL_5_PIN ) },
		{ MATRIX_COL_6_ADDR, _BV( MATRIX_COL_6_PIN ) },
		{ MATRIX_COL_7_ADDR, _BV( MATRIX_COL_7_PIN ) }
};
struct port_addr_pin matrix_rows[8] = {
		{ MATRIX_ROW_0_ADDR, _BV( MATRIX_ROW_0_PIN ) },
		{ MATRIX_ROW_1_ADDR, _BV( MATRIX_ROW_1_PIN ) },
		{ MATRIX_ROW_2_ADDR, _BV( MATRIX_ROW_2_PIN ) },
		{ MATRIX_ROW_3_ADDR, _BV( MATRIX_ROW_3_PIN ) },
		{ MATRIX_ROW_4_ADDR, _BV( MATRIX_ROW_4_PIN ) },
		{ MATRIX_ROW_5_ADDR, _BV( MATRIX_ROW_5_PIN ) },
		{ MATRIX_ROW_6_ADDR, _BV( MATRIX_ROW_6_PIN ) },
		{ MATRIX_ROW_7_ADDR, _BV( MATRIX_ROW_7_PIN ) }
};



void display_byte(uint8_t showMe)
{
    for(uint8_t i=0; i<8; i++){
    	if(showMe & _BV(7 - i)){
    		*(matrix_rows[i].port_addr) |= matrix_rows[i].port_pin;
    	}else{
    		*(matrix_rows[i].port_addr) &= (uint8_t)~matrix_rows[i].port_pin;
    	}
    }
}

void display_byte_line(uint8_t showMe, uint8_t line)
{
	for(uint8_t i=0; i<8; i++){
		*(matrix_cols[i].port_addr) |= matrix_cols[i].port_pin;
	}
	display_byte(showMe);
	*(matrix_cols[ line ].port_addr) &= (uint8_t)~ matrix_cols[ line ].port_pin;
}

void display_image(uint8_t showMe[8])
{

}
