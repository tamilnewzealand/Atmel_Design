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

/*
 * Initializes Timer 0 with pre-scaler of 256. This timer is used
 * for timing the PostLoopCalc every 1 seconds.
 */
void Timer0Init() {
	TCCR0B |= (1 << CS02);
	TCNT0 = 0;
	DDRB |= (1 << 2);
	sei();
	tot0_overflow = 0;
	Ipk = 800;
	Vrms = 12.00;
	realPower = 9.60;
}

/*
 * Initializes Timer 1 with pre-scaler of 1024. This timer is used
 * for timing the USART transmission.
 */
void Timer1Init() {
	DDRD |= (1 << 2)|(1 << 3)|(1 << 4);
	TCCR1B |= (1 << CS11)|(1 << CS10);
	TCNT1 = 0;
	TIMSK1 |= (1 << TOIE1);
	tot1_overflow = 0;
}

/*
 * Timer 1 Overflow Interrupt handler. Increments overflow counter.
 */
ISR(TIMER1_OVF_vect) {
	tot1_overflow++;
}

/*
 * Initializes Timer 2 with pre-scaler of 1024. This timer is used
 * for timing the flashing of the blinking LED. Operates on 
 * interrupt basis.
 */
void Timer2Init() {
	TCCR2B |= (1 << CS22)|(1 << CS20);
	DDRB |= (1 << 2);
	TCNT2 = 0;
	TIMSK2 |= (1 << TOIE2);	
}

ISR(TIMER2_OVF_vect) {
	tot2_overflow++;
	if (tot2_overflow >= flashRate) {
		PORTB ^= (1 << 2);
		tot2_overflow = 0;
	}
}