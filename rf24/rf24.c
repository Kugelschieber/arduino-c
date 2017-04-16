#include "rf24.h"
#include "nRF24L01.h"
#include "../ard/pins.h"

// FIXME for testing, remove later
#include <util/delay.h>

const unsigned char RF24_POWER_DOWN = 1;
const unsigned char RF24_STANDBY_1 = 2;
const unsigned char RF24_STANDBY_2 = 3;
const unsigned char RF24_TX = 4;
const unsigned char RF24_RX = 5;

unsigned char _ce, _csn, _sck, _mo, _mi, _irq;

unsigned char rf24_serial_write(unsigned char);

void rf24_init(unsigned char ce, unsigned char csn, unsigned char sck, unsigned char mo, unsigned char mi, unsigned char irq){
	pin_mode(ce, OUTPUT);
	pin_mode(csn, OUTPUT);
	digital_write(csn, HIGH); // disable
	pin_mode(sck, OUTPUT);
	pin_mode(mo, OUTPUT);
	pin_mode(mi, INPUT);
	pin_mode(irq, OUTPUT);

	_ce = ce;
	_csn = csn;
	_sck = sck;
	_mo = mo;
	_mi = mi;
	_irq = irq;

	rf24_mode(RF24_POWER_DOWN);
}

void rf24_mode(unsigned char mode){
	switch(mode){
		case 1: // RF24_POWER_DOWN
			rf24_config_register(CONFIG, 0x00);
			break;
		case 2: // RF24_STANDBY_1
			//rf24_config_register(CONFIG, 1<<PWR_UP);
			break;
		case 3: // RF24_STANDBY_2
			break;
		case 4: // RF24_TX
			break;
		case 5: // RF24_RX
			break;
	}
}

void rf24_config_register(unsigned char reg, unsigned char value){
	rf24_serial_write(W_REGISTER|(reg&REG_MASK));
	rf24_serial_write(value);
}

unsigned char rf24_read_register(unsigned char reg){
	return rf24_serial_write(R_REGISTER|(reg&REG_MASK));
}

unsigned char rf24_serial_write(unsigned char data){
	digital_write(_sck, LOW);
	digital_write(_csn, LOW); // chip enable
	unsigned char i = 0, rx = 0;

	for(i = 0; i < 8; i++){
		// write bit
		if(data&(1<<(7-i))){
			digital_write(_mo, HIGH);
		}
		else{
			digital_write(_mo, LOW);
		}

		// read bit
		digital_write(_sck, HIGH); // clock
		rx <<= 1;

		if(digital_read(_mi)){
			rx |= 0x01;
		}

		digital_write(_sck, LOW); // clock
	}

	digital_write(_csn, HIGH); // chip disable

	return rx;
}
