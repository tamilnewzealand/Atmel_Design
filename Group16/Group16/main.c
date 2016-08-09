/*
 * Group16.c
 *
 * Created: 4/08/2016 10:10:21 p.m.
 * Author : ssit662
 */ 

#include "prototypes16.h"
#include "funtions16.h"


/* declare global variables here*/

int main( void )
{
	uart_init(MYUBRR);
	while (1){
		//read array
		uart_transmit(0b00100101);
	}
}