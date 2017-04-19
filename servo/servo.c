#include "servo.h"
#include "../ard/pins.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define MAX_SERVOS 8
#define SERVO_DELTA_MIN_US 1000
#define SERVO_DELTA_US 1000

Servo* servos[MAX_SERVOS];
unsigned char servo_i = 0;

void servo_init(Servo* servo){
	if(servo_i >= MAX_SERVOS){
		return;
	}

	servos[servo_i] = servo;
	servo_i++;

	sei();
	pin_mode((*servo).pin, OUTPUT);
	(*servo).val = 0;

	TCCR1A = 0x00;
	TCCR1B = (1<<WGM12);
	TCCR1C = 0x00;

	// 20ms, 1.5ms
	OCR1A = 1250;
	OCR1B = 3000;

	// enable interrupt on timer match
	TIMSK1 = (1<<OCIE1A)|(1<<OCIE1B);

	// start interrupt, prescaler 8
	TCCR1B |= 1<<CS12;
}

void servo_set(Servo* servo, unsigned char val){
	(*servo).val = val;
}

ISR(TIMER1_COMPA_vect){
	unsigned char i = 0;

	for(i = 0; i < servo_i; i++){
		digital_write(7, HIGH);
		_delay_us(1000+(1000/255)*(*servos[i]).val);
		digital_write(7, LOW);
	}
}
