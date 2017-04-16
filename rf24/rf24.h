#ifndef RF24_H_
#define RF24_H_

void rf24_init(unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);
void rf24_config(unsigned char, unsigned char);
void rf24_rx_addr(unsigned char*);
void rf24_tx_addr(unsigned char*);

void rf24_send(unsigned char*);
unsigned char rf24_is_sending();

unsigned char rf24_data_ready();
void rf24_get_data(unsigned char*);

unsigned char rf24_status();
void rf24_config_register(unsigned char, unsigned char);
unsigned char rf24_read_register(unsigned char);

#endif
