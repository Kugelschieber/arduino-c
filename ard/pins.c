#include "pins.h"
#include <avr/io.h>
#include <avr/interrupt.h>

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

void analog_read_duty_cycle();
unsigned char map_analog_pin(unsigned char);

void pins_init(){
	sei();

	// enable ADC (128 bit ADPS scaling factor 0x07) to read analog values
	ADCSRA = _BV(ADEN)|_BV(ADIE)|0x07;

	// clear timer to compare match for PWM output
	TCCR0A |= _BV(WGM01)|_BV(WGM00);
	TCCR1A |= _BV(WGM01)|_BV(WGM00);
	TCCR2A |= _BV(WGM21)|_BV(WGM20);

	// enable interrupt on timer overflow for PWM output
	TIMSK0 |= _BV(TOIE0);
}

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
	else if(pin < A0){
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
		pin -= A0;

		if(mode == INPUT){
			DDRC &= ~_BV(pin);
		}
		else{
			DDRC |= _BV(pin);
		}
	}
}

int digital_read(unsigned char pin){
	if(pin > A7){
		return 0;
	}

	if(pin < 8){
		// digital pin 0-7
		return PIND&_BV(pin) ? 1 : 0;
	}
	else if(pin < A0){
		// digital pin 8-13
		pin -= 8;
		return PINB&_BV(pin) ? 1 : 0;
	}

	// analog pin 0-7
	return analog_read(pin) > 512 ? 1 : 0;
}

void digital_write(unsigned char pin, unsigned char value){
	if(pin > A7){
		return;
	}

	if(pin < 8){
		// digital pin 0-7
		if(value == HIGH){
			PORTD |= _BV(pin);
		}
		else{
			PORTD &= ~_BV(pin);
		}
	}
	else if(pin < A0){
		// digital pin 8-13
		pin -= 8;

		if(value == HIGH){
			PORTB |= _BV(pin);
		}
		else{
			PORTB &= ~_BV(pin);
		}
	}
	else{
		// analog pin 0-7
		pin -= A0;

		if(value == HIGH){
			PORTC |= _BV(pin);
		}
		else{
			PORTC &= ~_BV(pin);
		}
	}
}

unsigned int analog_read(unsigned char pin){
	pin = map_analog_pin(pin);

	if(pin > 7){
		return 0;
	}

	// disable digital input buffer (DIDR0)
	ADMUX = _BV(REFS0)|pin;
	DIDR0 |= _BV(pin);
	ADCSRA |= _BV(ADSC); // start conversion

	// wait for it to finish
	while(ADCSRA&_BV(ADSC));

	// return 10 bit value
	return ADC;
}

void analog_write(unsigned char pin, unsigned char value){
	// write digital if possible
	if(value == 0){
		digital_write(pin, LOW);
		return;
	}
	else if(value == 255){
		digital_write(pin, HIGH);
		return;
	}

	if(pin != 3 && pin != 5 && pin != 6 && pin != 9 && pin != 10 && pin != 11){
		return;
	}

	// 1. clear timer on compare match (pins_init)
	// 2. set interrupt on overflow (pins_init) and value to compare to
	// 3. set timer scaling to 1, which starts the timer
	if(pin == 3){
		TCCR2A |= _BV(COM2B1);
		OCR2B = value;
		TCCR2B |= _BV(CS20)|_BV(CS21);
	}
	else if(pin == 5){
		TCCR0A |= _BV(COM0B1);
		OCR0B = value;
		TCCR0B |= _BV(CS00)|_BV(CS02);
	}
	else if(pin == 6){
		TCCR0A |= _BV(COM0A1);
		OCR0A = value;
		TCCR0B |= _BV(CS00)|_BV(CS02);
	}
	else if(pin == 9){
		TCCR1A |= _BV(COM1A1);
		OCR1A = value;
		TCCR1B |= _BV(CS10)|_BV(CS11);
	}
	else if(pin == 10){
		TCCR1A |= _BV(COM1B1);
		OCR1B = value;
		TCCR1B |= _BV(CS10)|_BV(CS11);
	}
	else if(pin == 11){
		TCCR2A |= _BV(COM2A1);
		OCR2A = value;
		TCCR2B |= _BV(CS20)|_BV(CS21);
	}
}

// maps A0-A7 to 0-7
unsigned char map_analog_pin(unsigned char pin){
	if(pin > 7){
		return pin-A0;
	}

	return pin;
}

// analog to digital converter interrupt handler
// required, but does not need to do anything
ISR(ADC_vect){}
