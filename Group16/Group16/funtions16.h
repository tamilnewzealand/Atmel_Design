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

void uart_init(uint8_t myboard)
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
	
	while (!((1<<UDRE0) && UCSR0A));
		UDR0 = data;	
	
	
	// you can put delay statement here
	_delay_ms(50);              // 50ms delay PER CALL! 
								//(i.e. 16 x 50m = 0.8 seconds delay overall per number transmitted)
}