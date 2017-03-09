#include "pins.h"
#include <avr/io.h>

const unsigned char LOW = 0x00;
const unsigned char HIGH = 0x01;

void digitalWrite(unsigned char pin, unsigned char value){
	if(pin > 13){
		return;
	}

	// TODO turn off pwm

	if(pin < 8){
		// pin 0-7
		DDRD |= _BV(DDD0+pin);

		if(value == HIGH){
			PORTD |= _BV(DDD0+pin);
		}
		else{
			PORTD &= ~_BV(DDD0+pin);
		}
	}
	else{
		// pin 8-13
		DDRB |= _BV(DDB0+pin);

		if(value == HIGH){
			PORTB |= _BV(DDB0+pin);
		}
		else{
			PORTB &= ~_BV(DDB0+pin);
		}
	}
}

void analogWrite(unsigned char pin, unsigned char value){
	if(pin > 7){
		return;
	}

	// TODO turn off pwm

	DDRC |= _BV(DDC0+pin);

	if(value == HIGH){
		PORTC |= _BV(DDC0+pin);
	}
	else{
		PORTC &= ~_BV(DDC0+pin);
	}
}