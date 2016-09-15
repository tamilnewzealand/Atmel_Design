/*
 * spi.c
 *
 * Created: 14/09/2016 4:20:24 p.m.
 *  Author: ssit662
 */ 

#include "spi.h"

void SPI1Init(void) {
	// Set MOSI, SCK, SS as Output
	DDRB = (1<<DDB5)|(1<<DDB3)|(1<<DDB2);
	
	// Enable SPI, Set as Master, Pre-scaler: Fosc/128
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR1)|(1<<SPR0)|(1<<CPOL)|(1<<CPHA);
}

void SPI1SendByte(uint8_t data) {
	// Load data into the buffer
	SPDR = data;
	
	//Wait until transmission complete
	while(!(SPSR & (1<<SPIF)));
}