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

#include "adc.h"

void InitADC() {
	// Select Vref to internal AREF
	ADMUX |= (1<<REFS0);
	
	//set prescaller to 128 and enable ADC
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN)|(1<<ADIE);
	
	isr_chan = V_Filter;
	count = 0;
	
	ADCSRA |= (1<<ADSC);
	
	sei();
}

ISR(ADC_vect) {
// check and store ADC reading to appropriate vector
if (isr_chan == V_Filter) {
		analog_input_voltage = ADC;
		isr_chan = I_Filter;
	} else if (isr_chan == I_Filter) {
		analog_input_current = ADC;
		isr_chan = V_Filter;
}

// setup ADC for next reading
ADMUX = (ADMUX & 0xF0) | (isr_chan & 0x0F);
ADCSRA |= (1<<ADSC);

if (isr_chan == V_Filter) AmpCalc();
if (isr_chan == I_Filter) VoltCalc();
}

void InitComp() {
	ACSR |= (1<<ACIE);
	cyclecount = 0;
	sei();
}

ISR (ANALOG_COMP_vect) {
	//Check for rising or falling edge
	if (ACSR & (1<<ACO)) cyclecount++;
	if (cyclecount > 10) {
		total_numberOfSamples = numberOfSamples;
		total_sumV = sumV;
		total_sumI = sumI;
		total_sumP = sumP;
		cyclecount = 0;
		
		//Reset accumulators
		sumV = 0;
		sumI = 0;
		sumP = 0;
		numberOfSamples = 0;
	}
}