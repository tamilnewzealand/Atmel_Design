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

#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include <math.h>
#include <avr/io.h>

#define Mid_Supply 4
#define I_Filter 5
#define V_Filter 3

volatile uint16_t analog_input;

volatile float sumV;
volatile float total_sumV;
volatile float Vrms;

volatile float sumI;
volatile float total_sumI;
volatile float Irms;

volatile float sumP;
volatile float total_sumP;
volatile float realPower;

volatile int16_t numberOfSamples;
volatile int16_t total_numberOfSamples;

volatile int32_t filteredV;
volatile int32_t filteredI;

volatile int32_t offsetV;
volatile int32_t offsetI;


void AlgInit();
void VoltCalc();
void AmpCalc();
void PostLoopCalc();

#endif /* ALGORITHM_H_ */