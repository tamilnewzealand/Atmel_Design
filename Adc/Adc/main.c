/*
 * Adc.c
 *
 * Created: 25/08/2016 6:15:35 p.m.
 * Author : ssit662
 */ 

#include <stdio.h>
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#define USART_BAUDRATE 9600
#define UBRR_VALUE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
#define POT 50

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
	digit = (uint8_t)value / 10;
	digit |= (1 << 6);
	digit |= (1 << 5);
	digit &=~ (1 << 4);
	USART0SendByte(digit);
	
	digit = (uint8_t)value % 10;
	digit |= (1 << 6);
	digit &=~ (1 << 5);
	digit |= (1 << 4);
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
	
	// Select Vref=AVcc
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
int main() {
	
	//double vbg;
	double potval;
	//initialize ADC
	
	InitADC();
	//Initialize USART0
	
	USART0Init();
	
	//assign our stream to standart I/O streams
	//stdout=&usart0_str;
	
	while(1) {
		
		//reading potentiometer value and recalculating to Ohms
		potval=(double)POT/1024*ReadADC(0);
		
		USART0TransmitNumber(potval);
		
		_delay_ms(5);
	
	}
}

