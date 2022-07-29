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

	serial_write("Writing data\n\r", 14);
	at28c256_write(0, 0x7D);
	at28c256_write(1, 0x12);
	at28c256_write(2, 0x9F);
	at28c256_write(3, 0x5A);

	serial_write("Reading data\n\r", 14);
	int i;
	char out[20];

	for(i = 0; i < 4; i++) {
		unsigned char value = at28c256_read(i);
		const int n = sprintf(out, "0x%x\n\r", value);
		serial_write(out, n);
	}
}

void loop() {}
