/*
 * life.c
 *
 *  Created on: 23.01.2010
 *      Author: brunql
 */
#include <avr/io.h>
#include "life.h"

uint8_t population[8] = {
            0b01111110,
            0b10000001,
            0b10111001,
            0b10101001,
            0b10111001,
            0b10000001,
            0b10000001,
            0b01111110
};

uint8_t buffer_pop[8];

uint8_t get_neighbours(uint8_t row, uint8_t col)
{
	uint8_t result = 0;
    for(uint8_t i = (((uint8_t)(row-1) == (uint8_t)0xff) ? 0 : (row-1));
    		i <= row + 1;
    		i++)
    {
        if (i < 8){
			for(uint8_t j = (((uint8_t)(col-1) == (uint8_t)0xff) ? 0 : (col-1));
					j <= col + 1;
					j++)
			{
				if(j < 8 && is_set_population(i, j)) result++;
			}
        }
    }
    if (is_set_population(row, col)) result--; // del self form result
    return result;
}

void generate_next_population(void)
{
    for(uint8_t row=0; row<8; row++){
        for(uint8_t col=0; col<8; col++){
            uint8_t neighbours = get_neighbours(row, col);
            if (is_set_population(row, col)){ // has life
                if (neighbours < 2 || neighbours > 3){
                    buffer_pop[row] &= (uint8_t)~_BV(7 - col); // kill life
                }else{
                	buffer_pop[row] |= _BV(7 - col); // save life
                }
            }else if (neighbours == 3){ // hasn't life
                buffer_pop[row] |= _BV(7 - col); // create life
            }
        }
    }

    for(uint8_t row=0; row<8; row++){
        population[row] = buffer_pop[row];
    }
}
