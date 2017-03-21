#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "serial.h"
#include "pins.h"

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
	pin_mode(A4, INPUT);
}

void loop(){
	// digital input/output example
	/*if(digital_read(10) && digital_read(8)){
		digital_write(11, HIGH);
	}
	else{
		digital_write(11, LOW);
	}*/

	// anlog input example
	int analog = analog_read(A4);
	char out[15];
	sprintf(out, "%d", analog);
	serial_write(out, 15);

	_delay_ms(25);
}
