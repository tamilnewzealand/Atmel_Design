/*
 * Adc.c
 *
 * Created: 25/08/2016 6:15:35 p.m.
 * Author : ssit662
 */ 

#include <stdio.h>
#include <math.h>
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#define USART_BAUDRATE 9600
#define UBRR_VALUE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
#define VREF 5
#define V_Filter 0
#define I_Filter_High 1
#define I_Filter_Low 2
#define Mid_Supply 5

void USART0Init(void) {
	// Set baud rate
	UBRR0H = (uint8_t)(UBRR_VALUE>>8);
	UBRR0L = (uint8_t)UBRR_VALUE;
	
	// Set frame format to 8 data bits, no parity, 1 stop bit
	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
	
	//enable transmission and reception
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
}

int USART0SendByte(uint8_t data) {
	//wait while previous byte is completed
	while(!(UCSR0A&(1<<UDRE0))){};
	
	// Transmit data
	UDR0 = data;
	return 0;
}

void USART0TransmitNumber(double value) {
	
	uint8_t digit;
	digit = (uint8_t)value % 10;
	digit |= (1 << 6);
	digit |= (1 << 5);
	digit |= (1 << 4);
	USART0SendByte(digit);
	
	value *= 10;
	digit = (uint8_t)value % 10;
	digit |= (1 << 6);
	digit &=~ (1 << 5);
	digit &=~ (1 << 4);
	USART0SendByte(digit);
	
	value *= 10;
	digit = (uint8_t)value % 10;
	digit &=~ (1 << 6);
	digit |= (1 << 5);
	digit &=~ (1 << 4);
	USART0SendByte(digit);
	
	USART0SendByte(0x0A);
	
}

void InitADC() {
	// Select Vref to internal AREF
	ADMUX |= (1<<REFS0);
	
	//set prescaller to 128 and enable ADC
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);
}

uint16_t ReadADC(uint8_t ADCchannel) {
	//select ADC channel with safety mask
	ADMUX = (ADMUX & 0xF0) | (ADCchannel & 0x0F);
	
	//single conversion mode
	ADCSRA |= (1<<ADSC);
	
	// wait until ADC conversion is complete
	while( ADCSRA & (1<<ADSC) );
	return ADC;
}

uint16_t CalcRMS(uint8_t ADCchannel) {
	double value = 0x00000000;
	uint8_t i;
	uint16_t x;
	// Approximating 64 successive ADC Readings
	for (i = 0; i < 63; i++) {
		x = ReadADC(ADCchannel);
		value += (double)x * (double)x;
	}
	value = sqrt(value);
	value /= 8;
	return (uint16_t)value;
}

int main() {
	
	double value;
	
	InitADC();	
	USART0Init();
	while(1) {
		value = (double)VREF/1024*CalcRMS(V_Filter);
		USART0TransmitNumber(value);
	}
}