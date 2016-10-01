/*
 * algorithm.c
 *
 * Created: 25/08/2016 6:15:35 p.m.
 * Author : ssit662
 */

#include "algorithm.h"

void VoltCalc() {
	int32_t shiftedFCL;
	
	lastSampleV=sampleV;
	sampleV = analog_input_voltage;
	
	// Filters below are based on ideas from:
	// http://openenergymonitor.org/emon/buildingblocks/digital-filters-for-offset-removal
	
	shiftedFCL = shifted_filterV + (int32_t)((sampleV-lastSampleV)<<8);
	shifted_filterV = shiftedFCL - (shiftedFCL>>8);
	filteredV = (shifted_filterV+128)>>8;
	
	sumV += filteredV * filteredV;
}
void AmpCalc() {
	int32_t shiftedFCL;
	
	numberOfSamples++;
	
	lastSampleI=sampleI;
	sampleI = analog_input_current;
	
	shiftedFCL = shifted_filterI + (int32_t)((sampleI-lastSampleI)<<8);
	shifted_filterI = shiftedFCL - (shiftedFCL>>8);
	filteredI = (shifted_filterI+128)>>8;
	
	sumI += filteredI * filteredI;
	sumP += filteredV * filteredI;
}

void PostLoopCalc() {
	//Calculation of the root of the mean of the voltage and current squared (rms)
	//Calibration co-efficients applied.
	
	Vrms = (double)(49.5 / 1023.0) * sqrt(total_sumV / total_numberOfSamples);
	
	Irms = (double)(4.73 / 1023.0) * sqrt(total_sumI / total_numberOfSamples);

	//Calculation power values
	realPower = (double)(49.5 / 1023.0) * (double)(4.73 / 1023.0) * total_sumP / total_numberOfSamples;

	//Reset accumulators
	sumV = 0;
	sumI = 0;
	sumP = 0;
	numberOfSamples = 0;
}
