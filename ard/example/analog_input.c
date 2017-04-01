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
	pins_init();
	serial_init(9600);

	pin_mode(A1, INPUT);
	pin_mode(A2, INPUT);
}

unsigned char pwm = 0;

void loop(){
	int analog1 = analog_read(A1);
	int analog2 = analog_read(A2);
	
	char out[15];
	sprintf(out, "%d %d", analog1, analog2);
	serial_write(out, 15);

	_delay_ms(25);
}
