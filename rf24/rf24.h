#ifndef RF24_H_
#define RF24_H_

#include "register.h"

void rf24_init(unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);
void rf24_tx_addr(unsigned char*);
void rf24_rx_addr(unsigned char*);
void rf24_send(char*); // length is fixed and set on initialization
void rf24_receive(char*); // length is fixed and set on initialization

#endif
