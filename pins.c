#include "pins.h"
#include <avr/io.h>

const unsigned char LOW = 0x00;
const unsigned char HIGH = 0x01;
const unsigned char INPUT = 0x00;
const unsigned char OUTPUT = 0x01;

void digitalPinMode(unsigned char pin, unsigned char mode){
	if(pin > 13){
		return;
	}

	if(pin < 8){
		if(mode == INPUT){
			DDRD &= ~_BV(DDD0+pin);
		}
		else{
			DDRD |= _BV(DDD0+pin);
		}
	}
	else{
		pin -= 8;

		if(mode == INPUT){
			DDRB &= ~_BV(DDB0+pin);
		}
		else{
			DDRB |= _BV(DDB0+pin);
		}
	}
}

int digitalRead(unsigned char pin){
	if(pin > 13){
		return 0;
	}

	// TODO turn off pwm

	if(pin < 8){
		// pin 0-7
		return PIND&_BV(DDD0+pin);
	}

	// pin 8-13
	pin -= 8;
	return PINB&_BV(DDB0+pin);
}

void digitalWrite(unsigned char pin, unsigned char value){
	if(pin > 13){
		return;
	}

	// TODO turn off pwm

	if(pin < 8){
		// pin 0-7
//		DDRD |= _BV(DDD0+pin);

		if(value == HIGH){
			PORTD |= _BV(DDD0+pin);
		}
		else{
			PORTD &= ~_BV(DDD0+pin);
		}
	}
	else{
		// pin 8-13
		pin -= 8;
//		DDRB |= _BV(DDB0+pin);

		if(value == HIGH){
			PORTB |= _BV(DDB0+pin);
		}
		else{
			PORTB &= ~_BV(DDB0+pin);
		}
	}
}

void analogPinMode(unsigned char pin, unsigned char mode){
	if(pin > 7){
		return;
	}

	if(mode == INPUT){
		DDRC &= ~_BV(DDC0+pin);
	}
	else{
		DDRC |= _BV(DDC0+pin);
	}
}

int analogRead(unsigned char pin){
	if(pin > 7){
		return 0;
	}

	return PINC&_BV(DDC0+pin);
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