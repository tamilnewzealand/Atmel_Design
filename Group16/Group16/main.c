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
	uint8_t array[10] = {12,15,67,89,72,34,49,59,61,52};
	
	uart_init(MYUBRR);
	while (1){
		//read array
		for(uint8_t i=0;i<10;i++) {
			uint8_t variable = array[i];
			uart_transmit(variable);
			_delay_ms(500);
		}
		
	}
}