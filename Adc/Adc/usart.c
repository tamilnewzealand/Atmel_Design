/*
 * usart.c
 *
 * Created: 25/08/2016 6:15:35 p.m.
 * Author : ssit662
 */

#include "usart.h"

void USART0Init(void) {
	// Set baud rate
	UBRR0H = (uint8_t)(UBRR_VALUE>>8);
	UBRR0L = (uint8_t)UBRR_VALUE;
	
	// Set frame format to 8 data bits, no parity, 1 stop bit
	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
	
	//enable transmission and reception
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
}

int USART0SendByte(uint8_t data) {
	//wait while previous byte is completed
	while(!(UCSR0A&(1<<UDRE0))){};
	
	// Transmit data
	UDR0 = data;
	return 0;
}

void USART0TransmitNumber(double value, uint8_t type) {
	uint8_t digit;
	digit = (uint8_t)value % 10;
	digit |= (1 << 6);
	digit |= (1 << 5);
	digit |= (1 << 4);
	USART0SendByte(digit);
	
	value *= 10;
	digit = (uint8_t)value % 10;
	digit |= (1 << 6);
	digit &=~ (1 << 5);
	digit &=~ (1 << 4);
	USART0SendByte(digit);
	
	value *= 10;
	digit = (uint8_t)value % 10;
	digit &=~ (1 << 6);
	digit |= (1 << 5);
	digit &=~ (1 << 4);
	USART0SendByte(digit);
	
	if (type == 0) USART0SendByte(0x0A);
	if (type == 1) USART0SendByte(0x0B);
	if (type == 2) USART0SendByte(0x0C);
}
