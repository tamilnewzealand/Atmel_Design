/*
 * algorithm.c
 *
 * Created: 25/08/2016 6:15:35 p.m.
 * Author : ssit662
 */

#include "algorithm.h"

double CalcRMS(double peak) {
	double value = 0x00000000;
	uint8_t i;
	for (i = 0; i < 63; i++) {
		value += (double)adc_vol_result[i] * (double)adc_vol_result[i];
	}
	value = sqrt(value);
	value /= 8;
	value -= peak;
	value *= ((double)106.6/(double)6.6);
	value *= (double)5.00/1024.0;
	return value;
}

double CalcPeak() {
	double value = 0x00000000;
	uint8_t i;
	for (i = 0; i < 63; i++) {
		value += (double)adc_amp_result[i] * (double)adc_amp_result[i];
	}
	value = sqrt(value);
	value /= 8;
	value *= sqrt(2);
	value *= (double)5.00/1024.0;
	return value;
}

double CalcPower(){
	double value = 0x00000000;
	uint8_t i;
	for (i = 0; i < 63; i++) {
		value += (double)adc_amp_result[i] * (double)adc_vol_result[i];
	}
	value /= 64;
	return value;
}