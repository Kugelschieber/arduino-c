#include "pins.h"
#include <avr/io.h>

const unsigned char LOW = 0x00;
const unsigned char HIGH = 0x01;
const unsigned char INPUT = 0x00;
const unsigned char OUTPUT = 0x01;

// analog pins (digital range from 0 to 13)
const unsigned char A0 = 0x0e;
const unsigned char A1 = 0x0f;
const unsigned char A2 = 0x10;
const unsigned char A3 = 0x11;
const unsigned char A4 = 0x12;
const unsigned char A5 = 0x13;
const unsigned char A6 = 0x14;
const unsigned char A7 = 0x15;

unsigned char map_analog_pin(unsigned char);

void pin_mode(unsigned char pin, unsigned char mode){
	if(pin > A7){
		return;
	}

	if(pin < 8){
		// digital pin 0-7
		if(mode == INPUT){
			DDRD &= ~_BV(pin);
		}
		else{
			DDRD |= _BV(pin);
		}
	}
	else if(pin < 14){
		// digital pin 8-13
		pin -= 8;

		if(mode == INPUT){
			DDRB &= ~_BV(pin);
		}
		else{
			DDRB |= _BV(pin);
		}
	}
	else{
		// analog pin 0-7
		pin -= 14;

		if(mode == INPUT){
			DDRC &= ~_BV(pin);
		}
		else{
			DDRC |= _BV(pin);
		}
	}
}

int digital_read(unsigned char pin){
	if(pin > 13){
		return 0;
	}

	// TODO turn off pwm

	if(pin < 8){
		// pin 0-7
		return PIND&_BV(pin) ? 1 : 0;
	}

	// pin 8-13
	pin -= 8;
	return PINB&_BV(pin) ? 1 : 0;
}

void digital_write(unsigned char pin, unsigned char value){
	if(pin > 13){
		return;
	}

	// TODO turn off pwm

	if(pin < 8){
		// pin 0-7
		if(value == HIGH){
			PORTD |= _BV(pin);
		}
		else{
			PORTD &= ~_BV(pin);
		}
	}
	else{
		// pin 8-13
		pin -= 8;

		if(value == HIGH){
			PORTB |= _BV(pin);
		}
		else{
			PORTB &= ~_BV(pin);
		}
	}
}

int analog_read(unsigned char pin){
	pin = map_analog_pin(pin);

	if(pin > 7){
		return 0;
	}

	// TODO use ADC

	ADMUX = 0xf0|pin;
	ADCSRA |= _BV(pin);
	while(ADCSRA&_BV(pin));

	return ADC;
}

void analog_write(unsigned char pin, int value){
	pin = map_analog_pin(pin);

	if(pin > 7){
		return;
	}

	// TODO turn off pwm

	if(value == HIGH){
		PORTC |= _BV(pin);
	}
	else{
		PORTC &= ~_BV(pin);
	}
}

// maps A0-A7 to 0-7
unsigned char map_analog_pin(unsigned char pin){
	if(pin > 7){
		return pin-A0;
	}

	return pin;
}
