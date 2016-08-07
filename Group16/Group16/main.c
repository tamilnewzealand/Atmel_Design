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
	uart_init();
	uint8_t TXBUF[] = {17, 23, 29, 37, 43, 53, 59, 67, 83, 97};
	uint8_t txindex = 0;
	uint8_t data;
	uint8_t digit;
	while (1){
		//read array
		data = TXBUF[txindex];
		digit = data % 10;
		uart_transmit(digit);
		digit = data / 10;
		uart_transmit(digit);
		txindex++;
	}
}