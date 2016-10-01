/*
 * timer.h
 *
 * Created: 29/09/2016 9:07:02 p.m.
 *  Author: ssit662
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "algorithm.h"

// global variable to count the number of overflows
volatile uint8_t tot0_overflow;
volatile uint8_t tot1_overflow;

void Timer0Init();
ISR(TIMER0_OVF_vect);
void Timer1Init();
ISR(TIMER1_OVF_vect);
void USART0TransmitNumber(double value, uint8_t type);

#endif /* TIMER_H_ */