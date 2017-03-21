#ifndef PINS_H_
#define PINS_H_

extern const unsigned char LOW;
extern const unsigned char HIGH;
extern const unsigned char INPUT;
extern const unsigned char OUTPUT;

// rename underscore
void digitalPinMode(unsigned char, unsigned char);
int digitalRead(unsigned char);
void digitalWrite(unsigned char, unsigned char);

void analogPinMode(unsigned char, unsigned char);
int analogRead(unsigned char);
void analogWrite(unsigned char, unsigned char);

#endif
