/*
 * Group16.c
 *
 * Created: 4/08/2016 10:10:21 p.m.
 * Author : ssit662
 */ 

#include "prototypes16.h"
#include "funtions16.h"
#include <util/delay.h>


/* declare global variables here*/

int main(void)
{
	/*
	convert 10 bit input to decimal
	
	//compute power
	
	//convert decimal value to digits and record respective position
	//record position of decimal point
	
	//convert decimal digit to binary
	
	//left shift a 0, the position (as 2 bits), whether the decimal point is present (0 or 1) and the 4 bit digit.
		
	//convert the created number to decimal
	
	//correctly input it in array (watch out for position) 
	*/
	
	/*ADC POLLING STEPS
	1. Make the pin for selected ADC channel an input pin
	
	2. Turn on ADC module of AVR because it is disabled upon power on reset to save power
	
	3. Select conversion speed using ADPS2 : 0 
	
	4. Select Voltage reference (use REFS0 and REFS1) and input channel (use Mux3 : 0 in ADMUX)
	
	5. Activate the start conversion bit by writing a one to ADSC bit of ADCSRA
	
	6. Wait for conversion to be completed by polling the ADIF bit ADCSRA register
	
	7. After the ADIF bit has gone high, read the ADCL and ADCH. Read ADCL before ADCH.
	
	8. If you want to read selected channel again, go back to step 5. 
	
	9. If you want to select another Vref source or input channel, go back to step 4
	*/
	
	/*ADC INTERRUPTS STEPS
	1. Make the pin for selected ADC channel an input pin 
	
	2. Turn on ADC module of AVR because it is disabled upon power on reset to save power
	
	3. Select conversion speed using ADPS2 : 0 
	
	4. Select Voltage reference (use REFS0 and REFS1) and input channel (use Mux4 : 0 in ADMUX)
	
	5. Set ADIE bit high 
	
	6. Activate the start conversion bit by writing a one to ADSC bit of ADCSRA
	
	7. Upon completion ADIF bit has gone high, (you can read the ADCL and ADCH in ISR)
	
	8. After the ADIF bit has gone high, it will force the CPU to jump to the ADC interrupt handler
	*/
	
	/*TIMER POLLING STEPS
	1. Load the TCNT0 with the initial value. 
	
	2. Load the value into TCCR0 register, indicating which mode is to be used and the prescaler option.
	
	3. Keep monitoring the timer overflow flag (TOV0) to see if it is raised. 
	
	4. Clear TOV0 flag for the next round. 
	
	5. Go back to step 1 to load TCNT0 again.
	*/
	
	/*
	Note code is available for polling and interrupts on Nadeem's sheet (number 5).
	*/
	
	uint8_t array[4] = {102,71,40,9};
	//prints out 1,2,3,4 in sequence from left to right on SSD in order
	//0d97 == 0110 0001
	//0d66 == 0110 0110
	//0d65 == 0010 0011
	//0d4  == 0000 0100
	
	//print out 6,7,8,9 in sequence from left to right on SSD in order
	//0d102 == 0110 0110
	//0d71  == 0100 0111
	//0d40  == 0010 1000
	//0d9   == 0000 1001
	
	uart_init(/*MYUBRR*/);
	while (1){
		//read array
		for(uint8_t i=0;i<4;i++) {
			uint8_t variable = array[i];
			uart_transmit(variable);
			_delay_ms(4.1666);	//want to have it very low so it appears like a 4 digit number shown (around 2-3 milliseconds)
		}
		
	}
}