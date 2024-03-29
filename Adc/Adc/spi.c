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
	SPDR1 = data;
	while(!(SPSR1 & (1<<SPIF)));
}

/*
 * Sets the gain of the MCP6S91 to the value passed in.
 */
void SetMcp6S91Gain(uint8_t gan) {
	SPI1SendByte(MCP6S91_GAIN_CMD);
	SPI1SendByte(gan);
}

/* 
 * Initializes the MCP6S91 state machine, by filling all of it's
 * registers with appropriate data. As this is a single channel 
 * model, the channel needs to be set only once. The gain is set
 * to 1 during the initialization.
 */
void Mcp6S91Init(void) {
	SPI1Init();
	SPI1SendByte(MCP6S91_CHANNEL_CMD);
	SPI1SendByte(0x00);
	gain = 1;
	SetMcp6S91Gain(MCP6S91_GAIN_1);
}

/*
 * Function looks at the value of Ipk and auto-magically sets
 * an appropriate gain for the PGA using the previous gain set
 * function.
 */
void Mcp6S91AutoAdjust(void) {
	if (old_maxI > 900) {
		if (gain == 8) {
			SetMcp6S91Gain(MCP6S91_GAIN_4);
			gain = 4;
		} else if (gain == 4) {
			SetMcp6S91Gain(MCP6S91_GAIN_2);
			gain = 2;
		} else if (gain == 2) {
			SetMcp6S91Gain(MCP6S91_GAIN_1);
			gain = 1;
		}
	}
	
	if (old_maxI < (890 - (512/gain))) {
		if (gain == 1) {
			SetMcp6S91Gain(MCP6S91_GAIN_2);
			gain = 2;
		} else if (gain == 2) {
			SetMcp6S91Gain(MCP6S91_GAIN_4);
			gain = 4;
		} else if (gain == 4) {
			SetMcp6S91Gain(MCP6S91_GAIN_8);
			gain = 8;
		}
	}
}