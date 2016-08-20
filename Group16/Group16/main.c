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
	//convert 10 bit input to decimal
	
	//compute power
	
	//convert decimal value to digits and record respective position
	//record position of decimal point
	
	//convert decimal digit to binary
	
	//left shift a 0, the position (as 2 bits), whether the decimal point is present (0 or 1) and the 4 bit digit.
		
	//convert the created number to decimal
	
	//correctly input it in array (watch out for position)
	
	
	
	
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