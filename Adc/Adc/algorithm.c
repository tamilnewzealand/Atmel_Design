/*   
 * Wireless Energy Monitor
 *
 * Copyright (C) 2016 Sakayan Sitsabesan <ssit662@aucklanduni.ac.nz>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "algorithm.h"

// Algorithm below is based on ideas from ATMEL AVR465: Single-Phase Power/Energy Meter.

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
}
