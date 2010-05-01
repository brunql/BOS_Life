/*
 * life.h
 *
 *  Created on: 23.01.2010
 *      Author: brunql
 */

#ifndef LIFE_H_
#define LIFE_H_

#define is_set_population(ROW, COL) (population[(ROW)] & _BV(7 - COL))

extern uint8_t population[8];

extern void generate_next_population(void);

#endif /* LIFE_H_ */
