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

#define VREF 3.3F
#define Mid_Supply 3
#define I_Filter 2
#define V_Filter 0

volatile uint16_t adc_vol_result[64];
volatile uint16_t adc_amp_result[64];

double CalcRMS(double peak);
double CalcPeak();
double CalcPower();

#endif /* ALGORITHM_H_ */