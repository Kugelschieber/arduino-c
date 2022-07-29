#include <util/delay.h>
#include <stdio.h>
#include "ard/serial.h"
#include "ard/pins.h"
#include "at28c256/at28c256.h"

void prepare();
void loop();

int main() {
	prepare();

	while(1){
		loop();
	}
}

void prepare() {
	pins_init();
	serial_init(9600);
	at28c256_init(2, 13, 4, 3, 5, 6, 7, 8, 9, 10, 11, 12);

	at28c256_write(0x0000, 0x7B); // 123
	at28c256_write(0x0001, 0x2A); // 42
}

void loop() {
	serial_write("Test\n\r", 6);
	_delay_ms(1000);
}
