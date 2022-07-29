#include <util/delay.h>
#include <stdio.h>
#include "ard/serial.h"
#include "ard/pins.h"
#include "ard/util.h"
#include "rf24/rf24.h"
#include "rf24/nRF24L01.h"

//#define TX
#define PAYLOAD 32 // byte

unsigned char rx_addr[5] = {0xE7, 0xE7, 0xE7, 0xE7, 0xE7};
unsigned char tx_addr[5] = {0xD7, 0xD7, 0xD7, 0xD7, 0xD7};

void prepare();
void loop();
void tx();
void rx();

int main(){
	prepare();

	while(1){
		loop();
	}
}

void prepare(){
	pins_init();
	serial_init(9600);

	pin_mode(A1, OUTPUT); // green
	pin_mode(A2, OUTPUT); // red

	rf24_init(7, 6, 5, 4, 3, 2);
	rf24_config(2, PAYLOAD);

#ifdef TX
	rf24_rx_addr(rx_addr);
	rf24_tx_addr(tx_addr);
#else
	rf24_rx_addr(tx_addr);
	rf24_tx_addr(rx_addr);
#endif

	digital_write(A1, HIGH);
	_delay_ms(300);
	digital_write(A1, LOW);
}

void loop(){
#ifdef TX
	tx();
#else
	rx();
#endif
}

void tx(){
	_delay_ms(10);
	digital_write(A1, LOW);
	digital_write(A2, LOW);
	unsigned char data[PAYLOAD] = "Hello, World! What's going on?";

	rf24_send(data);
	while(rf24_is_sending());
	unsigned char status = rf24_status();

	if(status&(1<<TX_DS)){
		digital_write(A1, HIGH);
	}
	else{
		digital_write(A2, HIGH);
	}
}

void rx(){
	digital_write(A1, LOW);
	digital_write(A2, LOW);

	if(rf24_data_ready()){
		unsigned char data[PAYLOAD];

		rf24_get_data(data);
		digital_write(A1, HIGH);
		serial_write((char*)data, PAYLOAD);

		_delay_ms(100);
	}
}
