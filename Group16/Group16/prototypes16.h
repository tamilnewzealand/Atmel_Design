/*
 * Group16.c
 *
 * Created: 4/08/2016 10:10:21 p.m.
 * Author : ssit662
 */ 

#include <avr/io.h>
#define F_CPU 20000000UL // Clock Speed
#define BAUD 9600
#include <util/delay.h>
#define MYUBRR ((F_CPU /(16UL*BAUD))-1)

void uart_init ( unsigned int MYUBRR);
void uart_transmit (uint_8 data );