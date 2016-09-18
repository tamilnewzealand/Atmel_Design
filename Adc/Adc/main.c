/*
 * main.c
 *
 * Created: 25/08/2016 6:15:35 p.m.
 * Author : ssit662
 */ 

#include <stdio.h>
#include "adc.h"
#include "usart.h"
#include "spi.h"
	
int main(void) {
	uint8_t i;
	double ipk;
	double vrms;
	double power;
	InitADC();
	USART0Init();
	SPI1Init();
	while(1) {
		ipk = CalcRMS(1);
		ipk *= (double)sqrt(2)/(double)0.25;
		for (i = 0; i < 199; i++) {
			USART0TransmitNumber(ipk, 0);
			_delay_ms(5);
		}
		vrms = CalcRMS(0);
		vrms *= (double)106.6/(double)6.6;
		for (i = 0; i < 199; i++) {
			USART0TransmitNumber(vrms, 1);
			_delay_ms(5);
		}
		power = CalcPower();
		for (i = 0; i < 199; i++) {
			USART0TransmitNumber(power, 2);
			_delay_ms(5);
		}
	}
}