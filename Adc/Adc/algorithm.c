/*
 * algorithm.c
 *
 * Created: 25/08/2016 6:15:35 p.m.
 * Author : ssit662
 */

#include "algorithm.h"

double CalcRMS(uint8_t type) {
	double value = 0x00000000;
	uint8_t i;
	if (type == 0) {
		for (i = 0; i < 63; i++) {
			value += (double)adc_vol_result[i] * (double)adc_vol_result[i];
		}
	} else if (type == 1) {
		for (i = 0; i < 63; i++) {
			value += (double)adc_amp_result[i] * (double)adc_amp_result[i];
		}
	} else return 0;
	value *= VREF/(double)32768.0;
	value -= (double)2.0*offset*offset;
	value = sqrt(value);
	return value;
}

double CalcPower(){
	double value = 0x00000000;
	uint8_t i;
	uint16_t adc_amp_approx[64];
	
	// rectangular approximation of current
	for (i = 0; i < 63; i++) {
		adc_amp_approx[i] = (adc_amp_result[i] + adc_amp_result[i+1] ) / 2;
	}
	
	for (i = 0; i < 63; i++) {
		value += (double)adc_amp_approx[i] * (double)adc_vol_result[i];
	}
	value /= 64;
	value *= VREF/(double)1024.0;
	return value;
}