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

#include "timer.h"

void Timer0Init() {
	TCCR0B |= (1 << CS02);
	TCNT0 = 0;
	tot0_overflow = 0;
	Irms = 0.80;
	Vrms = 12.00;
	realPower = 9.60;
}

void Timer1Init() {
	TCCR1B |= (1 << CS11)|(1 << CS10);
	TCNT1 = 0;
	TIMSK1 |= (1 << TOIE1);
	tot1_overflow = 0;
}

ISR(TIMER1_OVF_vect) {
	tot1_overflow++;
}

void Timer2Init() {
	TCCR1B |= (1 << CS22)|(1 << CS20);
	DDRB |= (2 << 0);
	TCNT2 = 0;
	TIMSK2 |= (1 << TOIE2);
	PORTB |= (2 << 0);
}

ISR(TIMER2_OVF_vect) {
	tot2_overflow++;
	if (tot2_overflow == 61 && flashRate == 1) PORTB &=~ (2 << 0);
	if (tot2_overflow == 122 && flashRate == 2) PORTB &=~ (2 << 0);
	if (tot2_overflow == 183 && flashRate == 3) PORTB &=~ (2 << 0);
	if (tot2_overflow == 244) {
		tot2_overflow = 0;
		PORTB |= (2 << 0);
	}
}