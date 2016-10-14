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

/*
 * Initializes the USART0 Interface of the ATmega328PB
 * for transmission. Sets the baud rate to 9600 and frame
 * format to 8 bits, no parity with 1 stop bit.
 */
void USART0Init(void) {
	UBRR0H = (uint8_t)(UBRR_VALUE>>8);
	UBRR0L = (uint8_t)UBRR_VALUE;
	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
	UCSR0B |= (1<<TXEN0);
}

/*
 * Transmits one byte of data through USART.
 * Is passed in the data to be sent as 'data'.
 * Uses polling mechanism to ensure complete transmission.
 */
void USART0SendByte(uint8_t data) {
	while(!(UCSR0A&(1<<UDRE0))){};
	UDR0 = data;
}

/* 
 * Encodes a double value passed into the function into 
 * packets that are suitable for the CPLD device used 
 * in this project to decode.
 * 
 * | Value  | Type |     Range    | Units
 * ----------------------------------------
 * | I(pk)  |   0  |  000 -> 999  | mA
 * | V(rms) |   1  | 10.0 -> 19.9 | V
 * | Power  |   2  | 0.00 -> 9.99 | W
 * -----------------------------------------
 */
void USART0TransmitNumber(double value, uint8_t type) {
	uint8_t digit = 0;
	
	// Digit 1000
	if (type == 0) digit = 0x60 | (uint8_t)((uint16_t)value / 100);
	if (type == 1) digit = 0x61;
	if (type == 2) digit = 0x70 | ((uint8_t)value % 10);
	USART0SendByte(digit);
	
	// Digit 100
	if (type == 0) digit = ((uint8_t)(value / 10) % 10) | 0x40;
	if (type == 1) digit = ((uint8_t)value % 10) | 0x50;
	if (type == 2) digit = ((uint8_t)(value * 10) % 10) | 0x40;
	USART0SendByte(digit);
	
	// Digit 10
	if (type == 0) digit = 0x20 | ((uint16_t)value % 10);
	if (type == 1) digit = 0x20 | ((uint8_t)(value * 10.0) % 10);
	if (type == 2) digit = 0x20 | ((uint8_t)(value * 100.0) % 10);
	USART0SendByte(digit);
	
	//Digit 1 (units)
	if (type == 0) USART0SendByte(0x0A);
	if (type == 1) USART0SendByte(0x0B);
	if (type == 2) USART0SendByte(0x0C);
}

/*
 * --------------  UNUSED FUNTION  --------------
 * Transmits string of characters one at a time
 * through the aforementioned transmit function.
 * Used for debugging purposes.
 * Not used in final project.
 */
void USART0SendString(char s[]) {
	int i =0;
	
	while (s[i] != '\0')
	{
		USART0SendByte(s[i]);
		i++;
	}
}