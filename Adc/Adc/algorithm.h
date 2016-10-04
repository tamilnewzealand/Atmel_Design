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
#define I_Filter 3
#define V_Filter 4

uint16_t analog_input_voltage;
uint16_t analog_input_current;

double realPower;
double Vrms;
double Irms;

int16_t lastSampleV;
int16_t sampleV;
int32_t shifted_filterV;
float sumV;
float total_sumV;

int16_t lastSampleI;
int16_t sampleI;
int32_t shifted_filterI;
float sumI;
float sumP;
float total_sumI;
float total_sumP;

uint16_t numberOfSamples;
uint16_t total_numberOfSamples;

uint8_t cyclecount;

int32_t filteredV;
int32_t filteredI;

void VoltCalc();
void AmpCalc();
void PostLoopCalc();

#endif /* ALGORITHM_H_ */