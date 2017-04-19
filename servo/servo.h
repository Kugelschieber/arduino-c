#ifndef SERVO_H_
#define SERVO_H_

typedef struct{
	unsigned char pin;
	unsigned char val; // 0-255
} Servo;

void servo_init(Servo*);
void servo_set(Servo*, unsigned char);

#endif
