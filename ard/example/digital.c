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

	pin_mode(11, OUTPUT);
	pin_mode(10, INPUT);
	pin_mode(8, INPUT);
}

void loop(){
	if(digital_read(10) && digital_read(8)){
		digital_write(11, HIGH);
	}
	else{
		digital_write(11, LOW);
	}

	_delay_ms(25);
}
