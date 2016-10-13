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

#include "algorithm.h"

// Algorithm below is based on ideas from ATMEL AVR465: Single-Phase Power/Energy Meter.

void AlgInit() {
	analog_input = 0;

	sumV = 0;
	total_sumV = 0;
	
	sumI = 0;
	sumP = 0;
	total_sumI = 0;
	total_sumP = 0;

	numberOfSamples = 0;
	total_numberOfSamples = 0;
	
	offsetV = 0;
	offsetI = 0;
}

void VoltCalc() {		
	// Filters below are based on ideas from:
	// http://openenergymonitor.org/emon/buildingblocks/digital-filters-for-offset-removal
	
    //offsetV = offsetV + ((analog_input-offsetV)/1024);
    //filteredV = analog_input - offsetV;
	filteredV = analog_input;
	
	sumV += filteredV * filteredV;
}

void AmpCalc() {
    //offsetI = offsetI + ((analog_input-offsetI)/1024);
    //filteredI = analog_input - offsetI;
	filteredI = analog_input;
	
	sumI += filteredI * filteredI;
	sumP += filteredV * filteredI;
	numberOfSamples++;
}

void PostLoopCalc() {			
	PORTD ^= (1 << 2);
	PORTD ^= (1 << 3);
	PORTD ^= (1 << 4);
			
	Vrms = sqrt(total_sumV / total_numberOfSamples);
	Vrms *= (float)0.0483871; // 49.5 / 1023
	
	Irms = sqrt(total_sumI / total_numberOfSamples);
	Irms *= (float)0.00462366; //4.73 / 1023

	realPower = (float)0.00022373 * total_sumP / (float)total_numberOfSamples;
}