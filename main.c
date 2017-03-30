#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "ard/serial.h"
#include "ard/pins.h"
#include "ard/util.h"

void prepare();
void loop();

int main(){
	prepare();

	while(1){
		loop();
	}
}

void prepare(){
	// enable global interrupts and serial port
	sei();
	serial_init(9600);

	// digital input/output example
	/*pin_mode(11, OUTPUT);
	pin_mode(10, INPUT);
	pin_mode(8, INPUT);*/

	// anlog input example
	/*pin_mode(A1, INPUT);
	pin_mode(A2, INPUT);*/

	// PWM example
	pin_mode(A1, INPUT);
	pin_mode(6, OUTPUT);
}

unsigned char pwm = 0;

void loop(){
	// digital input/output example
	/*if(digital_read(10) && digital_read(8)){
		digital_write(11, HIGH);
	}
	else{
		digital_write(11, LOW);
	}*/

	// anlog input example
	/*int analog1 = analog_read(A1);
	int analog2 = analog_read(A2);
	char out[15];
	sprintf(out, "%d %d", analog1, analog2);
	serial_write(out, 15);*/

	// PWM example
	int analog = map(analog_read(A1), 0, 1023, 0, 255);
	analog_write(6, analog);

	char out[15];
	sprintf(out, "%d", analog);
	serial_write(out, 15);

	_delay_ms(25);
}
