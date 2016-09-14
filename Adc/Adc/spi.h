/*
 * spi.h
 *
 * Created: 14/09/2016 4:20:38 p.m.
 *  Author: ssit662
 */ 


#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>
#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <util/delay.h>

void SPI1Init (void);
void SPI1SendByte(uint8_t data);

#endif /* SPI_H_ */