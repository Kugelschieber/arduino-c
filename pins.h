#ifndef PINS_H_
#define PINS_H_

extern const unsigned char LOW;
extern const unsigned char HIGH;
extern const unsigned char INPUT;
extern const unsigned char OUTPUT;

// rename underscore, unify digital and analog
void digital_pin_mode(unsigned char, unsigned char);
int digital_read(unsigned char);
void digital_write(unsigned char, unsigned char);

void analog_pin_mode(unsigned char, unsigned char);
int analog_read(unsigned char);
void analog_write(unsigned char, unsigned char);

#endif
