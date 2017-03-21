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
	/*pin_mode(11, OUTPUT);
	pin_mode(10, INPUT);
	pin_mode(8, INPUT);*/
	pin_mode(A4, INPUT);
}

void loop(){
	/*if(digital_read(10) && digital_read(8)){
		digital_write(11, HIGH);
	}
	else{
		digital_write(11, LOW);
	}*/

	if(analog_read(A4) > 0){
		serial_write("ok", 3);
	}
	else{
		serial_write("nope", 5);
	}
	
	_delay_ms(25);
}
