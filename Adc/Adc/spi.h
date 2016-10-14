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

#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>
#ifndef F_CPU
#define F_CPU 8000000UL
#endif
#include <util/delay.h>

#define MCP6S91_GAIN_CMD      0x40
#define MCP6S91_CHANNEL_CMD   0x41
#define MCP6S91_SHUTDOWN_CMD  0x20

#define MCP6S91_GAIN_1    0
#define MCP6S91_GAIN_2    1
#define MCP6S91_GAIN_4    2
#define MCP6S91_GAIN_5    3
#define MCP6S91_GAIN_8    4
#define MCP6S91_GAIN_10   5
#define MCP6S91_GAIN_16   6
#define MCP6S91_GAIN_32   7

volatile float Ipk;
uint8_t gain;

void SPI1Init (void);
void SPI1SendByte(uint8_t data);
void SetMcp6S91Gain(uint8_t gain);
void Mcp6S91Init(void);
void Mcp6S91AutoAdjust(void);

#endif /* SPI_H_ */