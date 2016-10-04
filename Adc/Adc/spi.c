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

void SPI1Init(void) {
	// Set MOSI, SCK, SS as Output
	DDRC |= (1<<1);
	DDRE |= (1<<3)|(1<<2);
	
	// Enable SPI, Set as Master, Pre-scaler: Fosc/128
	SPCR1 = (1<<SPE1)|(1<<MSTR1)|(1<<SPR11)|(1<<SPR10)|(1<<CPOL1)|(1<<CPHA1);
}

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

void PGAInit(void) {
	SPI1Init();
	SPI1SendByte(0x41);
	SPI1SendByte(0x00);
	SetMcp6S91Gain(MCP6S91_GAIN_1);
}