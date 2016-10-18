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
	AlgInit();
	InitADC();
	Mcp6S91Init();
	USART0Init();
	Timer1Init();
	Timer0Init();
	Timer2Init();
	InitComp();
	while(1) {
		if (TIFR0 & (1<<TOV0)) {
			TIFR0 = (1<<TOV0);
			tot0_overflow++;
			if (tot0_overflow < 85) {
				USART0TransmitNumber(Ipk, 0);
				} else if (tot0_overflow < 170) {
				USART0TransmitNumber(Vrms, 1);
				} else {
				USART0TransmitNumber(realPower, 2);
			}
			if (tot0_overflow == 255) tot0_overflow = 0;
		}
		if (tot1_overflow >= 3) {
			tot1_overflow = 0;
			PostLoopCalc();
		}
	}
}