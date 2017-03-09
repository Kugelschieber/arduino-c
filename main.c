#include <avr/io.h>
#include <util/delay.h>
#include "pins.h"

int main(){
	while(1){
		digitalWrite(5, HIGH);
		_delay_ms(1000);
		digitalWrite(5, LOW);
		_delay_ms(1000);
	}
}
