#include <util/delay.h>
#include <stdio.h>
#include "ard/serial.h"
#include "ard/pins.h"
#include "ard/util.h"
#include "rf24/rf24.h"
#include "rf24/nRF24L01.h"

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

	_delay_ms(50);
	rf24_init(7, 6, 5, 4, 3, 2);
	_delay_ms(200);
}

void loop(){
	rf24_read_register(STATUS);
	_delay_ms(5);
}
