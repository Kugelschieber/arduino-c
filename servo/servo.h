#ifndef SERVO_H_
#define SERVO_H_

// should not directly be modified!
// use functions instead
typedef struct{
	unsigned char no;
	unsigned char pin;
	unsigned char val; // 0-255
	unsigned char impuls; // 1-2ms
	unsigned int timer;
} Servo;

void servo_init(unsigned char, Servo*);
void servo_set(Servo*, unsigned char);
unsigned char servo_get(Servo*);

#endif
