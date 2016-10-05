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

#define Mid_Supply 5
#define I_Filter 4
#define V_Filter 3

volatile uint16_t analog_input_voltage;
volatile uint16_t analog_input_current;

volatile double realPower;
volatile double Vrms;
volatile double Irms;

volatile int16_t lastSampleV;
volatile int16_t sampleV;
volatile int32_t shifted_filterV;
volatile float sumV;
volatile float total_sumV;

volatile int16_t lastSampleI;
volatile int16_t sampleI;
volatile int32_t shifted_filterI;
volatile float sumI;
volatile float sumP;
volatile float total_sumI;
volatile float total_sumP;

volatile uint16_t numberOfSamples;
volatile uint16_t total_numberOfSamples;

volatile uint8_t cyclecount;

volatile int32_t filteredV;
volatile int32_t filteredI;

void VoltCalc();
void AmpCalc();
void PostLoopCalc();

#endif /* ALGORITHM_H_ */