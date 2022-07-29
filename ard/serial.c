#include "serial.h"
#include <avr/io.h>

void serial_init(unsigned int baud) {
	unsigned long baud_prescale = ((16000000UL/(baud*16UL)))-1;

	// enable transmitter and receiver
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);

	// set frame format (8 data bits, 2 stop bits)
	UCSR0C |= (1<<UCSZ00)|(1<<UCSZ01);

	// set baudrate (16 bit)
	UBRR0H  = baud_prescale>>8;
	UBRR0L  = baud_prescale;
}

void serial_write(char* data, unsigned int n) {
	unsigned int i;

	for(i = 0; i < n; i++){
		// wait for empty tx buffer
		while(!(UCSR0A&(1<<UDRE0)));

		// write to tx register
		UDR0 = data[i];
	}
}

void serial_read(char* data, unsigned int n) {
	unsigned int i;

	for(i = 0; i < n; i++){
		// wait until data is available in rx buffer
		while(!(UCSR0A&(1<<RXC0)));

		// store in data array
		data[i] = UDR0;
	}
}
