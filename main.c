#include <avr/io.h>
#include <util/delay.h>
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
	serial_init(9600);
	digital_pin_mode(5, OUTPUT);
	digital_pin_mode(11, OUTPUT);
}

void loop(){
	digital_write(5, HIGH);
	digital_write(11, HIGH);

	_delay_ms(1000);

	digital_write(5, LOW);
	digital_write(11, LOW);

	_delay_ms(1000);
}
