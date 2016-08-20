/*
 * Group16.c
 *
 * Created: 4/08/2016 10:10:21 p.m.
 * Author : ssit662
 */ 

#include <avr/io.h>			//required library
#define F_CPU 16000000UL	// Clock Speed
/*#define BAUD 9600*/			//Baud rate defined
#include <util/delay.h>		//include delay library
/*#define MYUBRR ((F_CPU /(16UL*BAUD))-1)*/	//define USART baud rate register

void uart_init (/*uint8_t myboard*/);	//compile function before running main (increases efficiency, i.e. speed)
void uart_transmit (uint8_t data );	//compile function before running main (increases efficiency, i.e. speed)