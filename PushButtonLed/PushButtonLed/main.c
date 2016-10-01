/*
 * PushButtonLed.c
 *
 * Created: 26/09/2016 11:22:05 a.m.
 * Author : WindowsUser
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

// initialize timer, interrupt and variable
void timer1_init()
{
	// set up timer with prescaler = 256
	TCCR0B |= (1 << CS02);
	
	// initialize counter
	TCNT0 = 0;
}

int main(void)
{
	// connect led to pin PB2
	DDRB |= (1 << 2);
	DDRB |= (0 << 7);
	
	// initialize timer
	timer1_init();
	
	// loop forever
	while(1)
	{
		if (PINB & (1<<PB7)) {
			if (TCNT0 >= 63) {
				PORTB ^= (1 << PB2);
				TCNT0 = 0;
			}
		} else {
			if (TCNT0 >= 125) {
				PORTB ^= (1 << PB2);
				TCNT0 = 0;
			}
		}
	}
}