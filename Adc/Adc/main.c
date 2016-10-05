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

#include "adc.h"
#include "usart.h"
#include "spi.h"
#include "timer.h"
#include "algorithm.h"
	
int main(void) {
	_delay_ms(1);
	InitADC();
	USART0Init();
	Mcp6S91Init();
	Timer1Init();
	Timer0Init();
	InitComp();
	while(1) {
		if (tot1_overflow >= 15) {
			tot1_overflow = 0;
			PostLoopCalc();
		}
	}
}