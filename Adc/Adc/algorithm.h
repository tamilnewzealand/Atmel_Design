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

#define Mid_Supply 5
#define I_Filter 3
#define V_Filter 4

uint16_t analog_input_voltage;
uint16_t analog_input_current;

double realPower, apparentPower, powerFactor, Vrms, Irms;

int16_t lastSampleV,sampleV;
int32_t shifted_filterV;
float sumV, total_sumV;

int16_t lastSampleI,sampleI;
int32_t shifted_filterI;
float sumI,sumP,total_sumI,total_sumP;

uint16_t numberOfSamples;
uint16_t total_numberOfSamples;

uint8_t last_cyclestate, cyclestate;

void InitAlgorithm();
void LoopCalc();
void PostLoopCalc();

#endif /* ALGORITHM_H_ */