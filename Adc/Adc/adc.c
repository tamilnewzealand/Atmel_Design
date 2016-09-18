/*
 * adc.c
 *
 * Created: 25/08/2016 6:15:35 p.m.
 * Author : ssit662
 */

#include "adc.h"

void InitADC() {
	// Select Vref to internal AREF
	ADMUX |= (1<<REFS0);
	
	//set prescaller to 128 and enable ADC
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);
	
	// taking a reading of the Mid_Supply
	isr_chan = Mid_Supply;
	ADMUX = (ADMUX & 0xF0) | (isr_chan & 0x0F);
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADSC));
	offset = ADC;
	
	// turn on ADC interrupts
	ADCSRA |= (1<<ADIE);
	
	//setup ADC for first sample
	isr_chan = V_Filter;
	count = 0;
	ADMUX = (ADMUX & 0xF0) | (isr_chan & 0x0F);	
	ADCSRA |= (1<<ADSC);
	
	//turn on global interrupts
	sei();
}

ISR(ADC_vect) {
	// check and store ADC reading to appropriate vector
	if (isr_chan == V_Filter) {
		adc_vol_result[count] = ADC;
		isr_chan = I_Filter;
	} else if (isr_chan == I_Filter) {
		adc_amp_result[count] = ADC;
		isr_chan = V_Filter;
		count++;
	}
	
	// setup ADC for next reading
	ADMUX = (ADMUX & 0xF0) | (isr_chan & 0x0F);
	if (count == 63) count = 0;
	ADCSRA |= (1<<ADSC);
}