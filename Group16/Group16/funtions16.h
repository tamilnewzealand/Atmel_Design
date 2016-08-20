/*
 * Group16.c
 *
 * Created: 4/08/2016 10:10:21 p.m.
 * Author : ssit662
 */ 

//For delay:
#define F_CPU 16000000UL //clock speed
#include <avr/io.h>
#include <util/delay.h>

void uart_init(/*uint8_t myboard*/)
{
	// Set baud rate using register UBRR0H and UBRR0L
	UBRR0H =  0; //(unsigned char) (myboard>>8);
	UBRR0L = 103; //(unsigned char) myboard;
	
	// Set frame format:
	// 8 bit data format, 1 stop bit, no parity bit
	UCSR0B|= (1<<TXEN0);				//enable transmitter
	UCSR0C|= (1<<UCSZ00)|(1<<UCSZ01);	//8 bit data format
	
}

void uart_transmit(uint8_t data )
{
	
	// Wait for empty transmit buffer
	// Put data into buffer, sends the data
	while (!((1<<UDRE0) && UCSR0A));	//Check if USART Data Register is Empty (1=yes) AND if USART Control and Status Register A is not 0 (then => 1), reverse the result and break out of the loop.
		UDR0 = data;	//Transfers the data to the UDR (USART data register)
}