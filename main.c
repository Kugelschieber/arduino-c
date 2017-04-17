#include <util/delay.h>
#include <stdio.h>
#include "ard/serial.h"
#include "ard/pins.h"
#include "ard/util.h"
#include "rf24/rf24.h"
#include "rf24/nRF24L01.h"

#define TX

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

	pin_mode(A1, OUTPUT); // green
	pin_mode(A2, OUTPUT); // red

	rf24_init(7, 6, 5, 4, 3, 2);
	rf24_config(2, 4);

#ifdef TX
	rf24_rx_addr(rx_addr);
	rf24_tx_addr(tx_addr);
#else
	rf24_rx_addr(tx_addr);
	rf24_tx_addr(rx_addr);
#endif
}

void loop(){
	digital_write(A2, LOW);
	_delay_ms(1000);
	digital_write(A1, LOW);
	digital_write(A2, HIGH);
	_delay_ms(1000);

#ifdef TX
	unsigned char data[4] = {1, 2, 3, 4};

	rf24_send(data);
	while(rf24_is_sending()){
		_delay_ms(20);
	}
	/*unsigned char status = rf24_status();

	if(status&(1<<TX_DS)){
		digital_write(A1, HIGH);
	}
	else{
		digital_write(A2, HIGH);
	}*/

	digital_write(A1, HIGH);
#else
	if(rf24_data_ready()){
		unsigned char data[4] = {0, 0, 0, 0};

		rf24_get_data(data);
		digital_write(A1, HIGH);

		char out[20];
		sprintf(out, "%d %d %d %d", data[0], data[1], data[2], data[3]);
		serial_write(out, 20);
	}
#endif
}
