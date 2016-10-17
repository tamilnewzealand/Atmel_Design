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
 * Low Pass filter is used to remove the DC Offset present in the signal.
 * To increase efficiency an ADC reading of the buffered 1V65 line is used
 * as the initial value of this filter.
 *
 * Filter below is based on ideas from:
 * http://openenergymonitor.org/emon/buildingblocks/digital-filters-for-offset-removal
 *
 * After filtering of the DC offset, the value is squared and added to a
 * temporary accumulator.
 */
void VoltCalc() {	
    filteredV = analog_input - offset;
	sumV += filteredV * filteredV;
}

/*
 * Uses same offset value as used for the Voltage to remove the DC offset.
 * Squared values are then added to the accumulators.
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
	Vrms *= (float)0.0483871; // 49.5 / 1023
	Vrms += 0.2;

	Ipk = total_maxI * (float)0.39312039;

	realPower = (float)0.01902196 * (float)(total_sumP / total_numberOfSamples);
	
	if (realPower > 4.875) {
		flashRate = 90;
		PORTD |= (1 << 2);
		PORTD |= (1 << 3);
		PORTD |= (1 << 4);
		PORTE |= (1 << 0);
	} else if (realPower > 3.25) {
		flashRate = 60;
		PORTD |= (1 << 2);
		PORTD |= (1 << 3);
		PORTD |= (1 << 4);
		PORTE &=~ (1 << 0);
	} else if (realPower > 1.625) {
		flashRate = 30;
		PORTD |= (1 << 2);
		PORTD |= (1 << 3);
		PORTD &=~ (1 << 4);
		PORTE &=~ (1 << 0);
	} else {
		flashRate = 0;
		PORTD |= (1 << 2);
		PORTD &=~ (1 << 3);
		PORTD &=~ (1 << 4);
		PORTE &=~ (1 << 0);
	}
	
	//Mcp6S91AutoAdjust();
}