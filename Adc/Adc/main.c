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
#include "timer.h"
#include "algorithm.h"
	
int main(void) {
	InitADC();
	USART0Init();
	SPI1Init();
	Timer1Init();
	Timer0Init();
	InitComp();
	while(1) {
		//do nothing as everything is done in ISR |;-)
	}
}