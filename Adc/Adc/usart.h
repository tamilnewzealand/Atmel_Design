/*
 * usart.h
 *
 * Created: 25/08/2016 6:15:35 p.m.
 * Author : ssit662
 */


#ifndef USART_H_
#define USART_H_

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

#define USART_BAUDRATE 9600
#define UBRR_VALUE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

void USART0Init(void);
int USART0SendByte(uint8_t data);
void USART0TransmitNumber(double value, uint8_t type);

#endif /* USART_H_ */