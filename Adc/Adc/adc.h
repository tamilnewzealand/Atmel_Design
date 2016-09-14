/*
 * adc.h
 *
 * Created: 25/08/2016 6:15:35 p.m.
 * Author : ssit662
 */


#ifndef ADC_H_
#define ADC_H_

#include <avr/interrupt.h>
#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <util/delay.h>
#include "algorithm.h"

#define VREF 3.3F
#define Mid_Supply 3
#define I_Filter 4
#define V_Filter 5

volatile uint8_t isr_chan;
volatile uint8_t count;
volatile uint16_t offset;

void InitADC();
ISR(ADC_vect);

#endif /* ADC_H_ */