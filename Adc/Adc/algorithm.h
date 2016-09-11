/*
 * algorithm.h
 *
 * Created: 25/08/2016 6:15:35 p.m.
 * Author : ssit662
 */


#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include <math.h>
#include <avr/io.h>

volatile uint16_t adc_vol_result[64];
volatile uint16_t adc_amp_result[64];

double CalcRMS();
double CalcPeak();
double CalcPower();

#endif /* ALGORITHM_H_ */