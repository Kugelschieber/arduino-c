#include <util/delay.h>
#include <stdio.h>
#include "../ard/serial.h"
#include "../ard/pins.h"
#include "../ard/util.h"

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
	pin_mode(13, OUTPUT);
}

void loop(){
	digital_write(13, LOW);
	_delay_ms(1000);
	digital_write(13, HIGH);
	_delay_us(1000000);
}
