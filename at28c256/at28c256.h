#ifndef AT28C256_H_
#define AT28C256_H_

void at28c256_init(unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);
void at28c256_write(unsigned short, unsigned char);
unsigned char at28c256_read(unsigned short);

#endif
