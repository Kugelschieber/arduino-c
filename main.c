#include <util/delay.h>
#include <stdio.h>
#include "ard/serial.h"
#include "ard/pins.h"
#include "at28c256/at28c256.h"

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
	at28c256_init(2, 13);
}

void loop(){
	at28c256_write(0x0001, 0);
	_delay_ms(1000);
	at28c256_write(0x8000, 0);
	_delay_ms(1000);
}
