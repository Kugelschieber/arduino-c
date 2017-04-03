#include "rf24.h"
#include "../ard/pins.h"

// CE = standby mode, CSN = SPI chip select
char payload_len, spi_ce, spi_csn, spi_sck, spi_mosi, spi_miso;

void reg_write(unsigned char, unsigned char);
void spi_transfer(unsigned char);

void rf24_init(unsigned char payload_length,
	unsigned char channel,
	unsigned char ce,
	unsigned char csn,
	unsigned char sck,
	unsigned char mosi,
	unsigned char miso){
	if(payload_length > 32){
		payload_length = 32;
	}

	payload_len = payload_length;
	spi_ce = ce;
	spi_csn = csn;
	spi_sck = sck;
	spi_mosi = mosi;
	spi_miso = miso;

	pin_mode(spi_ce, OUTPUT);
	pin_mode(spi_csn, OUTPUT);
	pin_mode(spi_sck, OUTPUT);
	pin_mode(spi_mosi, OUTPUT);
	pin_mode(spi_miso, INPUT);

	digital_write(spi_ce, LOW);
	digital_write(spi_csn, HIGH);

	reg_write(RF_CH, channel);
}

void rf24_tx_addr(unsigned char* addr){

}

void rf24_rx_addr(unsigned char* addr){

}

void rf24_send(char* data){

}

void rf24_receive(char* data){

}

void reg_write(unsigned char reg, unsigned char value){
	digital_write(spi_csn, LOW);
	spi_transfer(W_REGISTER|(REGISTER_MASK&reg));
	spi_transfer(value);
	digital_write(spi_csn, HIGH);
}

void spi_transfer(unsigned char data){
	unsigned char i = 0;
	unsigned char rx = 0;

	digital_write(spi_sck, LOW); // clock

	for(i = 0; i < 8; i++){
		// tx
		if(data&(1<<(7-i))){
			digital_write(spi_mosi, HIGH);
		}
		else{
			digital_write(spi_mosi, LOW);
		}

		digital_write(spi_sck, HIGH); // clock

		// rx
		rx <<= 1;

		if(digital_read(spi_miso) == HIGH){
			rx |= 0x01;
		}

		digital_write(spi_sck, LOW); // clock
	}
}
