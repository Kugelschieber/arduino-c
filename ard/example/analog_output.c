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
	pins_init();
	serial_init(9600);

	pin_mode(A1, INPUT);
	pin_mode(6, OUTPUT);
	pin_mode(11, OUTPUT);
}

unsigned char pwm = 0;

void loop(){
	int analog = map(analog_read(A1), 0, 1023, 0, 255);
	analog_write(11, analog);

	if(analog < 128){
		digital_write(6, HIGH);
	}
	else{
		digital_write(6, LOW);
	}

	char out[15];
	sprintf(out, "%d", analog);
	serial_write(out, 15);
}
