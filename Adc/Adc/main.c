/*
 * main.c
 *
 * Created: 25/08/2016 6:15:35 p.m.
 * Author : ssit662
 */ 

#include "adc.h"
#include "usart.h"
#include "spi.h"
	
int main(void) {
	uint8_t i;
	double value;
	InitADC();	
	USART0Init();
	SPI1Init();
	while(1) {
		value = CalcPeak();
		for (i = 0; i < 599; i++) {
			USART0TransmitNumber(value, 0);
			_delay_ms(5);
		}
		value = CalcRMS(value);
		for (i = 0; i < 599; i++) {
			USART0TransmitNumber(value, 1);
			_delay_ms(5);
		}
		value = CalcPower();
		for (i = 0; i < 599; i++) {
			USART0TransmitNumber(value, 2);
			_delay_ms(5);
		}
	}
}