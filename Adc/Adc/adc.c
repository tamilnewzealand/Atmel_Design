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

/*
 * Initializes the ADC of the ATmega328PB. Sets Vref to external 
 * AVcc voltage of 3.3V. Sets prescaller to 32 so Fadc = 250KHz.
 * Takes a sample of the mid supply channel and stores this value
 * in 'offset'. Sets up ADC for V_Filter sample, starts conversion
 * and enables interrupts.
*/
void InitADC() {
	// Select Vref to internal AREF
	ADMUX |= (1<<REFS0);
	
	//set prescaller to 32 and enable ADC
	ADCSRA |= (1<<ADPS2)|(1<<ADPS0)|(1<<ADEN)|(1<<ADIE);
	
	isr_chan = V_Filter;
	count = 0;
	
	ADCSRA |= (1<<ADSC);
	sei();
}


/*
 * ADC Interrupt handler.
 * Stores ADC sample, changes ADC Channel, and sets up ADC for 
 * next conversion. Also calls the appropriate calculation 
 * functions needed.
 */
ISR(ADC_vect) {
	if (isr_chan == V_Filter) {
		analog_input = ADC;
		isr_chan = I_Filter;
	} else if (isr_chan == I_Filter) {
		analog_input = ADC;
		isr_chan = V_Filter;
	}

	ADMUX = (ADMUX & 0xF0) | (isr_chan & 0x0F);
	ADCSRA |= (1<<ADSC);

	if (isr_chan == V_Filter) AmpCalc();
	if (isr_chan == I_Filter) VoltCalc();
}

/*
 * Initializes the internal Analog Comparator of the ATmega328PB.
 * Comparator triggers interrupt on falling edge of V_Filter.
 */
void InitComp() {
	ACSR |= (1<<ACIE)|(1<<ACIS1)|(1<<ACIS0);
	cyclecount = 0;
}

/*
 * Analog Comparator Interrupt Handler
 * Counts number of zero crossing in 'cyclecount'.
 * Once 100 zero crossings have been detected, the temporary
 * accumulators values are copied over to another set of 
 * variables and the accumulators are cleared.
 */
ISR (ANALOG_COMP_vect) {
	cyclecount++;
	if (cyclecount > 100) {
		total_numberOfSamples = numberOfSamples;
		total_sumV = sumV;
		total_sumI = sumI;
		total_sumP = sumP;
		cyclecount = 0;
		sumV = 0;
		sumI = 0;
		sumP = 0;
		numberOfSamples = 0;
	}
}