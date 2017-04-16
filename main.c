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

	pin_mode(A1, OUTPUT);
	pin_mode(A2, OUTPUT);

	rf24_init(7, 6, 5, 4, 3, 2);
	rf24_config(2, 4);

#ifdef TX
	rf24_rx_addr(rx_addr);
	rf24_tx_addr(tx_addr);
#else
	rf24_rx_addr(tx_addr);
	rf24_tx_addr(rx_addr);
#endif

	_delay_ms(1000);
}

void loop(){
	digital_write(A1, HIGH);
	digital_write(A2, LOW);

#ifdef TX
	unsigned char data[4] = {'t', 'e', 's', 't'};
	rf24_send(data);

	while(rf24_is_sending());

	unsigned char status = rf24_status();

	if(status&(1<<TX_DS)){
		digital_write(A2, HIGH);
	}
#else
	while(!rf24_data_ready());

	unsigned char data[4];
	rf24_get_data(data);

	char out[10];
	sprintf(out, "%d", data[0]);
	serial_write(out, 10);

	digital_write(A2, HIGH);
#endif

	digital_write(A1, LOW);
	_delay_ms(1000);
}
