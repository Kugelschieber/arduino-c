#include <avr/io.h>
#include <util/delay.h>
#include "serial.h"
#include "pins.h"

void loop();

int main(){
	/*digitalPinMode(6, INPUT);
	digitalPinMode(7, INPUT);
	digitalPinMode(12, OUTPUT);*/

	serial_init(9600);

	while(1){
		loop();
	}
}

void loop(){
	/*if(DDRB&0x10){
		digitalWrite(12, HIGH);
	}
	else{
		digitalWrite(12, LOW);
	}*/

	char buffer[5];
	serial_read(buffer, 5);
	serial_write(buffer, 5);

	_delay_ms(100);
}
