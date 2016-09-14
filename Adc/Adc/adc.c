/*
 * adc.c
 *
 * Created: 25/08/2016 6:15:35 p.m.
 * Author : ssit662
 */

#include "adc.h"

void InitADC() {
	
	// Delay to wait for system to load
	_delay_ms(1000);
	
	// Select Vref to internal AREF
	ADMUX |= (1<<REFS0);
	
	//set prescaller to 128 and enable ADC
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);
	
	// Read mid supply voltage once
	isr_chan = Mid_Supply;
	ADMUX = (ADMUX & 0xF0) | (isr_chan & 0x0F);
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADSC));
	offset = ADC;
	ADCSRA &=~ (1<<ADSC);
	
	//enable ADC interrupts
	ADCSRA |= (1<<ADIE);
	
	isr_chan = V_Filter;
	count = 0;
	
	sei();
}

ISR(ADC_vect) {
	if (isr_chan == V_Filter) {
		adc_vol_result[count] = ADC;
		isr_chan = I_Filter;
	} else if (isr_chan == I_Filter) {
		adc_amp_result[count] = ADC;
		isr_chan = V_Filter;
		count++;
	}
	
	ADMUX = (ADMUX & 0xF0) | (isr_chan & 0x0F);
	if (count == 63) count = 0;
	ADCSRA |= (1<<ADSC);
}