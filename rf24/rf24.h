#ifndef RF24_H_
#define RF24_H_

extern const unsigned char RF24_POWER_DOWN;
extern const unsigned char RF24_STANDBY_1;
extern const unsigned char RF24_STANDBY_2;
extern const unsigned char RF24_TX;
extern const unsigned char RF24_RX;

void rf24_init(unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);
void rf24_mode(unsigned char);

void rf24_config_register(unsigned char, unsigned char);
unsigned char rf24_read_register(unsigned char);

#endif
