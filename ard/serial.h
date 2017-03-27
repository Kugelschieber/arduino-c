#ifndef ARD_SERIAL_H_
#define ARD_SERIAL_H_

void serial_init(unsigned int);
void serial_write(char*, unsigned int);
void serial_read(char*, unsigned int);

#endif
