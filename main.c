#include <avr/io.h>
#include <util/delay.h>
#include "pins.h"

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((16000000UL/(USART_BAUDRATE*16UL)))-1)

void loop();

int main(){
	digitalPinMode(6, INPUT);
	digitalPinMode(7, INPUT);
	digitalPinMode(12, OUTPUT);

	// TODO verstehen und dann in Funktion packen
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
	UCSR0C |= (1<<UCSZ00)|(1<<UCSZ01);
	UBRR0H  = BAUD_PRESCALE>>8;
	UBRR0L  = BAUD_PRESCALE;

	while(1){
		loop();
	}
}

void loop(){
	/*if(DDRB&0x10){
		digitalWrite(12, HIGH);
	}
	else{
		digitalWrite(12, LOW);
	}*/

	// TODO verstehen und dann in Funktion packen
	while(!(UCSR0A&(1<<UDRE0)));
	UDR0 = 'h';
	while(!(UCSR0A&(1<<UDRE0)));
	UDR0 = 'e';
	while(!(UCSR0A&(1<<UDRE0)));
	UDR0 = 'l';
	while(!(UCSR0A&(1<<UDRE0)));
	UDR0 = 'l';
	while(!(UCSR0A&(1<<UDRE0)));
	UDR0 = 'o';
	while(!(UCSR0A&(1<<UDRE0)));
	UDR0 = '\n';
//	while(!(SPSR&(1<<SPIF)));

	_delay_ms(1000);
}
