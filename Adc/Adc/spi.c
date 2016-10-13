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

#include "spi.h"

/* 
 * Enables the SPI1 of the ATmega328PB as master with a prescaller
 * of 128, for communication with the PGA.
 */ 
void SPI1Init(void) {
	DDRC |= (1<<1);
	DDRE |= (1<<3)|(1<<2);
	SPCR1 = (1<<SPE1)|(1<<MSTR1)|(1<<SPR11)|(1<<SPR10);
	SPCR1 &=~ (1<<CPOL1);
	SPCR1 &=~ (1<<CPHA1);
}

/*
 * Transmits one byte of data through SPI1.
 * Is passed in the data to be sent as 'data'.
 * Uses polling mechanism to ensure complete transmission.
 */
void SPI1SendByte(uint8_t data) {
	// Load data into the buffer
	SPDR1 = data;
	
	//Wait until transmission complete
	while(!(SPSR1 & (1<<SPIF)));
}

void SetMcp6S91Gain(uint8_t gain) {
	SPI1SendByte(MCP6S91_GAIN_CMD);
	SPI1SendByte(gain);
}

void Mcp6S91Init(void) {
	SPI1Init();
	SPI1SendByte(MCP6S91_CHANNEL_CMD);
	SPI1SendByte(0x00);
	SetMcp6S91Gain(MCP6S91_GAIN_1);
}

void Mcp6S91AutoAdjust(void) {
	if (Ipk > 530 && gain != 1) {
		gain = 1;
		SetMcp6S91Gain(MCP6S91_GAIN_1);			
	} else if (Ipk > 265 && gain != 2) {
		gain = 2;
		SetMcp6S91Gain(MCP6S91_GAIN_2);
	} else if (Ipk > 130 && gain != 4) {
		gain = 4;
		SetMcp6S91Gain(MCP6S91_GAIN_4);
	}
}