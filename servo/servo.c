#include "servo.h"
#include "../ard/pins.h"
#include "../ard/util.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define MAX_SERVOS 8
#define SERVO_DELTA_MIN_US 1000
#define SERVO_DELTA_US 1000

Servo* servos[MAX_SERVOS];
unsigned char servo_n = 0, servo_i = 0;

void servo_init(unsigned char pin, Servo* servo){
	if(servo_n >= MAX_SERVOS){
		return;
	}

	(*servo).no = servo_n;
	(*servo).pin = pin;
	servos[servo_n] = servo;
	servo_n++;
	pin_mode(pin, OUTPUT);
	servo_set(servo, 128);

	sei();

	TCCR1A = 0x00;
	TCCR1B = (1<<WGM12);
	TCCR1C = 0x00;

	// 20ms, 1.5ms
	OCR1A = 1250;
	OCR1B = 94;

	// enable interrupt on timer match
	TIMSK1 = (1<<OCIE1A)|(1<<OCIE1B);

	// start interrupt, prescaler 8
	TCCR1B |= 1<<CS12;
}

void servo_set(Servo* servo, unsigned char val){
	// calculate impuls time
	(*servo).val = val;
	(*servo).impuls = (unsigned char)(63+(63.0/255.0)*((float)val)); // 63-125

	// set timer for first or other servos
	if((*servo).no == 0){
		(*servo).timer = (*servo).impuls;
	}
	else{
		(*servo).timer = (*servo).impuls+(*servos[(*servo).no-1]).timer;
	}

	// update following servos
	unsigned char i = 0;

	for(i = (*servo).no+1; i < servo_n; i++){
		(*servos[i]).timer = (*servos[i]).impuls+(*servos[i-1]).timer;
	}
}

unsigned char servo_get(Servo* servo){
	return (*servo).val;
}

ISR(TIMER1_COMPA_vect){
	if(servo_n > 0){
		servo_i = 0;
		OCR1B = (*servos[0]).timer;
		digital_write((*servos[0]).pin, HIGH);
	}
}

ISR(TIMER1_COMPB_vect){
	digital_write((*servos[servo_i]).pin, LOW);

	if(servo_i < servo_n-1){
		servo_i++;
		OCR1B = (*servos[servo_i]).timer;
		digital_write((*servos[servo_i]).pin, HIGH);
	}
}
