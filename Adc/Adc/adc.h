/*   
 * Wireless Energy Monitor
 *
 * Copyright (C) 2016 Sakayan Sitsabesan <ssit662@aucklanduni.ac.nz>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ADC_H_
#define ADC_H_

#include <avr/interrupt.h>
#include "algorithm.h"

volatile uint8_t isr_chan;
volatile uint8_t count;
volatile uint8_t cyclecount;

void InitADC();
ISR(ADC_vect);
void InitComp();
ISR (ANALOG_COMP_vect);

#endif /* ADC_H_ */