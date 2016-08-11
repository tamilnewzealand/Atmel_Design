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

int main( void )
{
	//convert decimal value to binary
	
	//filter out the first two bits to determine on which SSD to display
	//check the bit after to determine if decimal point present
	
	//convert last 4 bits to a single number in decimal
	
	//filter digits from the number (use % for 1000s, 100s and 10s and / for 1s)
	
	//display the number correctly
	
	
	
	
	uint8_t array[4] = {97,66,35,4};
	//prints out 1,2,3,4 in sequence from left to right on SSD in order
	//0d97 == 0110 0001
	//0d66 == 0110 0110
	//0d65 == 0010 0011
	//0d4  == 0000 0100
	
	uart_init(MYUBRR);
	while (1){
		//read array
		for(uint8_t i=0;i<4;i++) {
			uint8_t variable = array[i];
			uart_transmit(variable);
			_delay_ms(250);
		}
		
	}
}