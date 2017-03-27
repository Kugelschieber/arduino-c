#ifndef ARD_PINS_H_
#define ARD_PINS_H_

extern const unsigned char LOW;
extern const unsigned char HIGH;
extern const unsigned char INPUT;
extern const unsigned char OUTPUT;

extern const unsigned char A0;
extern const unsigned char A1;
extern const unsigned char A2;
extern const unsigned char A3;
extern const unsigned char A4;
extern const unsigned char A5;
extern const unsigned char A6;
extern const unsigned char A7;

void pin_mode(unsigned char, unsigned char);
int digital_read(unsigned char);
void digital_write(unsigned char, unsigned char);
unsigned int analog_read(unsigned char);
void analog_write(unsigned char, unsigned int);

#endif
