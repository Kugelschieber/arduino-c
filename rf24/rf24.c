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

unsigned char _ce, _csn, _sck, _mo, _mi, _irq, _payload_len;

void rf24_serial_transmit(unsigned char*, unsigned char);
unsigned char rf24_serial_write(unsigned char);

void rf24_init(unsigned char ce, unsigned char csn, unsigned char sck, unsigned char mo, unsigned char mi, unsigned char irq){
	pin_mode(ce, OUTPUT);
	digital_write(ce, LOW); // disable
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

	//rf24_mode(RF24_POWER_DOWN);
}

// channel in 1Mhz steps
void rf24_config(unsigned char channel, unsigned char payload_len){
	_payload_len = payload_len;

	rf24_config_register(RF_CH, channel&RF_CH_MASK); // 2.4Ghz + channel*1Mhz

	rf24_config_register(RX_PW_P0, 0x00); // auto ACK
	rf24_config_register(RX_PW_P1, payload_len&RX_PW_MASK); // data
	rf24_config_register(RX_PW_P2, 0x00); // unused...
	rf24_config_register(RX_PW_P3, 0x00);
	rf24_config_register(RX_PW_P4, 0x00);
	rf24_config_register(RX_PW_P5, 0x00);

	// low transmission rate, 0dBm
	rf24_config_register(RF_SETUP, (1<<RF_DR_LOW)|(0x03<<RF_PWR));

	// CRC
	rf24_config_register(CONFIG, (1<<EN_CRC)|(1<<CRCO));

	// auto ACK for pipe 0 and 1
	//rf24_config_register(EN_AA, 0x03);

	// rx address
	//rf24_config_register(EN_RXADDR, (1<<ERX_P0)|(1<<ERX_P1));

	// auto retransmit, 1000us, 15 retransmits
	rf24_config_register(SETUP_RETR, (0x03<<ARD)|(0x0F<<ARC));
}

void rf24_rx_addr(unsigned char* addr){
	rf24_serial_write(W_REGISTER|RX_ADDR_P1); // data pipe
	rf24_serial_transmit(addr, 5);
}

void rf24_tx_addr(unsigned char* addr){
	rf24_serial_write(W_REGISTER|RX_ADDR_P0); // auto ACK pipe address must match...
	rf24_serial_transmit(addr, 5);
	rf24_serial_write(W_REGISTER|TX_ADDR); // tx address
	rf24_serial_transmit(addr, 5);
}

/*void rf24_mode(unsigned char mode){
	switch(mode){
		case 1: // RF24_POWER_DOWN
			digital_write(_ce, LOW);
			rf24_config_register(CONFIG, 0x00);
			break;
		case 2: // RF24_STANDBY_1
			digital_write(_ce, LOW);
			rf24_config_register(CONFIG, 1<<PWR_UP);
			break;
		case 3: // RF24_STANDBY_2
			digital_write(_ce, HIGH);
			rf24_config_register(CONFIG, 1<<PWR_UP);
			break;
		case 4: // RF24_TX
			digital_write(_ce, HIGH);
			rf24_config_register(CONFIG, 1<<PWR_UP);
			break;
		case 5: // RF24_RX
			digital_write(_ce, HIGH);
			rf24_config_register(CONFIG, (1<<PWR_UP)|(1<<PRIM_RX));
			break;
	}
}*/

void rf24_config_register(unsigned char reg, unsigned char value){
	rf24_serial_write(W_REGISTER|(reg&REG_MASK));
	rf24_serial_write(value);
}

unsigned char rf24_read_register(unsigned char reg){
	return rf24_serial_write(R_REGISTER|(reg&REG_MASK));
}

void rf24_serial_transmit(unsigned char* data, unsigned char len){
	unsigned char i = 0;

	for(i = 0; i < len; i++){
		rf24_serial_write(data[(len-1-i)]);
	}
}

unsigned char rf24_serial_write(unsigned char data){
	digital_write(_sck, LOW);
	digital_write(_csn, LOW); // chip enable
	unsigned char i = 0, rx = 0;

	for(i = 0; i < 8; i++){
		_delay_ms(5);

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
	digital_write(_mo, LOW);

	return rx;
}
