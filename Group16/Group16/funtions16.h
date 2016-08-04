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
	// 8 data, 1 stop bit, no paritiy bit
	
	//Enable Transmitter
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