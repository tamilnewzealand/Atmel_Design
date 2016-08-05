/*
 * Group16.c
 *
 * Created: 4/08/2016 10:10:21 p.m.
 * Author : ssit662
 */ 

void uart_init(unsigned int MYUBRR)
{
	// Set baud rate using register UBRR0H and UBRR0L
	UBRR0H = (unsigned char) (MYUBRR>>8);
	UBRR0L = (unsigned char) MYUBRR;
	
	// Set frame format:
	// 8 bit data format, 1 stop bit, no parity bit
	UCSR0B|= (1<<TXEN0);				//enable transmitter
	UCSR0C|= (1<<UCSZ00)|(1<<UCSZ01);	//8 bit data format
	
}
void uart_transmit(uint8_t data )
{
	
	// Wait for empty transmit buffer
	// Put data into buffer, sends the data
	
	while (!((1<<UDRE0) && UCSR0A)){
		UDR0 = data;	
	}
	
	// you can put delay statement here
}