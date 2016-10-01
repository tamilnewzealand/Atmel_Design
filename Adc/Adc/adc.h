/*
 * adc.h
 *
 * Created: 25/08/2016 6:15:35 p.m.
 * Author : ssit662
 */


#ifndef ADC_H_
#define ADC_H_

#include <avr/interrupt.h>
#include "algorithm.h"

volatile uint8_t isr_chan;
volatile uint8_t count;

void InitADC();
ISR(ADC_vect);
void InitComp();
ISR (ANALOG_COMP_vect);

#endif /* ADC_H_ */