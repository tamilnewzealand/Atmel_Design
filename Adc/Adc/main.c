/*
 * main.c
 *
 * Created: 25/08/2016 6:15:35 p.m.
 * Author : ssit662
 */ 

#include "adc.h"
#include "usart.h"
	
int main(void) {
	uint8_t i;
	double value;
	uint8_t temp;
	InitADC();	
	USART0Init();
	while(1) {
		value = CalcPeak(adc_amp_result);
		for (i = 0; i < 599; i++) {
			USART0TransmitNumber(value, 0);
			_delay_ms(5);
		}
		value = CalcRMS(adc_vol_result);
		for (i = 0; i < 599; i++) {
			USART0TransmitNumber(value, 1);
			_delay_ms(5);
		}
		value = CalcPower(adc_vol_result, adc_amp_result);
		for (i = 0; i < 599; i++) {
			USART0TransmitNumber(value, 2);
			_delay_ms(5);
		}
	}
}