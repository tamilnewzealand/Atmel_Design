/*   
 * Wireless Energy Monitor
 *
 * Copyright (C) 2016 Sakayan Sitsabesan <ssit662@aucklanduni.ac.nz>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
	
	if (type == 0) USART0SendByte(0x70);
	else if (type == 1) USART0SendByte(0x61);
	else {
		digit = 0x70 | ((uint8_t)value % 10);
		USART0SendByte(digit);
	}
	
	if (type != 1) {
		value *= 10;
	}
	digit = (uint8_t)value % 10;
	if (type != 1) {
		digit |= 0x40;
		} else {
		digit |= 0x50;
	}
	USART0SendByte(digit);
	
	digit = 0x20 | ((uint8_t)(value * 10.0) % 10);
	USART0SendByte(digit);
	
	if (type == 0) USART0SendByte(0x0D);
	if (type == 1) USART0SendByte(0x0E);
	if (type == 2) USART0SendByte(0x0F);
}


void USART0SendString(char s[]) {
	int i = 0;
	
	while (s[i] != '\0')
	{
		USART0SendByte(s[i]);
		i++;
	}
}