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
	digitalPinMode(5, OUTPUT);
	digitalPinMode(11, OUTPUT);
}

void loop(){
	digitalWrite(5, HIGH);
	digitalWrite(11, HIGH);

	_delay_ms(1000);

	digitalWrite(5, LOW);
	digitalWrite(11, LOW);

	_delay_ms(1000);
}
