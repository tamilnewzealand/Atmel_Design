/*
 * timer.c
 *
 * Created: 29/09/2016 9:06:26 p.m.
 *  Author: ssit662
 */ 

#include "timer.h"

void Timer0Init() {
	TCCR0B |= (1 << CS02);
	TCNT0 = 0;
	TIMSK0 |= (1 << TOIE0);
	sei();
	tot0_overflow = 0;
	Irms = 0.80;
	Vrms = 12.00;
	realPower = 9.60;
}

ISR(TIMER0_OVF_vect) {
	tot0_overflow++;
	PORTB ^= (1 << 2); 
	if (tot0_overflow < 85) USART0TransmitNumber(Irms, 0);
	else if (tot0_overflow < 170) USART0TransmitNumber(Vrms, 1);
	else USART0TransmitNumber(realPower, 2);
	
	if (tot0_overflow == 255) tot0_overflow = 0;
}

void Timer1Init() {
	DDRB |= (1 << 2);
	DDRD |= (1 << 2)|(1 << 3)|(1 << 4);
	DDRE |= (1 << 0);
	TCCR1B |= (1 << CS11);
	TCNT1 = 0;
	TIMSK1 |= (1 << TOIE1);
	sei();
	tot1_overflow = 0;
}

ISR(TIMER1_OVF_vect) {
	tot1_overflow++;
	
	if (tot1_overflow >= 15)
	{
		PORTE ^= (1 << 0);
		PORTD ^= (1 << 2);
		PORTD ^= (1 << 3);
		PORTD ^= (1 << 4);		
		tot1_overflow = 0;
		PostLoopCalc();
	}
}