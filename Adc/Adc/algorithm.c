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
#include "spi.h"

/*
 * Algorithm below is based on ideas from ATMEL AVR465: Single-Phase Power/Energy Meter.
 *
 * Initializes values used in algorithms to zero and sets
 * some pins used as LEDs to outputs.
 */
void AlgInit() {
	DDRD |= (1 << 2)|(1 << 3)|(1 << 4);
	DDRE |= (1 << 0);

	filteredI = 0;
	sumV = 0;
	maxI = 1;
	sumP = 0;
	numberOfSamples = 0;
	offset = 512;
}

/*
 * After filtering of the DC offset, the value is squared and added to a
 * temporary accumulator.
 */
void VoltCalc() {	
    filteredV = analog_input - offset;
	sumV += filteredV * filteredV;
}

/*
 * Uses same offset value as used for the Voltage to remove the DC offset.
 * Current value is compared with current max and updated if necessary.
 * Voltage x Current value is added to the power accumulator.
 */
void AmpCalc() {
	filteredI = analog_input - offset;
	
	if (filteredI > maxI) maxI = filteredI;
	
	sumP += filteredV * filteredI;
	numberOfSamples++;
}

/*
 * This section of the algorithm is polled every 1 second. 
 * Calculates the Vrms, Ipk, realPower values.
 * Also controls the 4 LED bar based on power values.
 */
void PostLoopCalc() {		
	Vrms = sqrt(total_sumV / total_numberOfSamples);
	Vrms *= (float)0.0483871;
	Vrms += 0.2;
	
	old_maxI = total_maxI;
	Ipk = total_maxI * (float)0.65062;
	Ipk = 3.3005 * Ipk + 14.612;
	//Ipk /= gain;
	
	realPower = (float)0.00001902196 * (float)(total_sumP / total_numberOfSamples);
	realPower = realPower / 2.76595745;
	realPower = 13.092*realPower + 0.2853;
	realPower = 1.0455*realPower - 0.1614;
	
	if (realPower > 6.375) {
		flashRate = 0;
		PORTD |= (1 << 2);
		PORTD |= (1 << 3);
		PORTD |= (1 << 4);
		PORTE |= (1 << 0);
	} else if (realPower > 4.25) {
		flashRate = 15;
		PORTD |= (1 << 2);
		PORTD |= (1 << 3);
		PORTD |= (1 << 4);
		PORTE &=~ (1 << 0);
	} else if (realPower > 2.125) {
		flashRate = 8;
		PORTD |= (1 << 2);
		PORTD |= (1 << 3);
		PORTD &=~ (1 << 4);
		PORTE &=~ (1 << 0);
	} else {
		flashRate = 5;
		PORTD |= (1 << 2);
		PORTD &=~ (1 << 3);
		PORTD &=~ (1 << 4);
		PORTE &=~ (1 << 0);
	}
	
	//Mcp6S91AutoAdjust();
}