#include <util/delay.h>
#include <stdio.h>
#include "ard/serial.h"
#include "ard/pins.h"
#include "ard/util.h"
#include "rf24/rf24.h"

void prepare();
void loop();

int main(){
	prepare();

	while(1){
		loop();
	}
}

void prepare(){
	pins_init();
	serial_init(9600);
	pin_mode(2, OUTPUT);
	digital_write(2, LOW);
	rf24_init(32, 2, 8, 7, 6, 5, 4);
	digital_write(2, HIGH);
}

void loop(){
	

	_delay_ms(1000);
}
