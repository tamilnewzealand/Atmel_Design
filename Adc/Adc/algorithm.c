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
	sumI = 0;
	sumP = 0;
	numberOfSamples = 0;
	offsetV = 392;
	offsetI = 512;
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
    filteredV = analog_input - offsetI;
	filteredV -= (int32_t)((filteredI >> 3));
	sumV += filteredV * filteredV;
}

/*
 * Uses same offset value as used for the Voltage to remove the DC offset.
 * Squared values are then added to the accumulators.
 */
void AmpCalc() {
	filteredI = analog_input - offsetI;
	sumI += filteredI * filteredI;
	sumP += filteredV * filteredI;
	numberOfSamples++;
}

/*
 * This section of the algorithm is polled every 1 second. 
 * Calculates the Vrms, Irms, Ipk, realPower values.
 * Also controls the 4 LED bar based on power values.
 */
void PostLoopCalc() {		
	Vrms = sqrt(total_sumV / total_numberOfSamples);
	Vrms *= (float)0.0483871; // 49.5 / 1023
	Vrms = 0.447*Vrms + 7.5071; // Works only at mid resistance
	
	Irms = sqrt(total_sumI / total_numberOfSamples);
	Irms *= (float)0.057501; //0.00462366; //4.73 / 1023
	
	Ipk = Irms * 5;
	Ipk = 0.0004*Ipk*Ipk*Ipk-0.1531*Ipk*Ipk + 24.94*Ipk - 1048.9;

	realPower = (float)0.00022373 * total_sumP / (float)total_numberOfSamples;
	
	if (realPower > 6.375) {
		flashRate = 3;
		PORTD |= (1 << 2);
		PORTD |= (1 << 3);
		PORTD |= (1 << 4);
		PORTE |= (1 << 0);
	} else if (realPower > 4.25) {
		flashRate = 2;
		PORTD |= (1 << 2);
		PORTD |= (1 << 3);
		PORTD |= (1 << 4);
		PORTE &=~ (1 << 0);
	} else if (realPower > 2.125) {
		flashRate = 1;
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