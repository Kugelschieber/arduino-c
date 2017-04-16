#include <util/delay.h>
#include <stdio.h>
#include "ard/serial.h"
#include "ard/pins.h"
#include "ard/util.h"
#include "rf24/rf24.h"
#include "rf24/nRF24L01.h"

unsigned char rx_addr[5] = {0xE7, 0xE7, 0xE7, 0xE7, 0xE7};
unsigned char tx_addr[5] = {0xD7, 0xD7, 0xD7, 0xD7, 0xD7};

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

	_delay_ms(200);
	rf24_init(7, 6, 5, 4, 3, 2);
	_delay_ms(200);
	rf24_config(0x02, 0xFF);
	_delay_ms(200);
	rf24_rx_addr(rx_addr);
	_delay_ms(200);
	rf24_tx_addr(tx_addr);
	_delay_ms(200);
}

void loop(){
	_delay_ms(20);
}
