#include <util/delay.h>
#include <stdio.h>
#include "ard/serial.h"
#include "ard/pins.h"
#include "ard/util.h"
#include "servo/servo.h"

Servo servo1;
Servo servo2;
Servo servo3;

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
	servo_init(7, &servo1);
	servo_init(6, &servo2);
	servo_init(8, &servo3);
}

void loop(){
	servo_set(&servo1, 0);
	servo_set(&servo2, 255);
	servo_set(&servo3, 0);
	_delay_ms(500);
	servo_set(&servo1, 128);
	servo_set(&servo2, 128);
	servo_set(&servo3, 255);
	_delay_ms(500);
}
