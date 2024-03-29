#include <util/delay.h>
#include "at28c256.h"
#include "../ard/pins.h"

#include "../ard/serial.h"

unsigned char _ck, _addr, _oe, _we, _io0, _io1, _io2, _io3, _io4, _io5, _io6, _io7;

void at28c256_init(unsigned char ck, unsigned char addr, unsigned char oe, unsigned char we, unsigned char io0, unsigned char io1, unsigned char io2, unsigned char io3, unsigned char io4, unsigned char io5, unsigned char io6, unsigned char io7) {
	pin_mode(ck, OUTPUT);
	digital_write(ck, LOW); // disable
	pin_mode(addr, OUTPUT);
	digital_write(addr, LOW); // disable
    pin_mode(oe, OUTPUT);
	digital_write(oe, HIGH); // disable
    pin_mode(we, OUTPUT);
	digital_write(we, HIGH); // disable
	
    _ck = ck;
	_addr = addr;
    _oe = oe;
    _we = we;
    _io0 = io0;
    _io1 = io1;
    _io2 = io2;
    _io3 = io3;
    _io4 = io4;
    _io5 = io5;
    _io6 = io6;
    _io7 = io7;
}

void set_addr(unsigned short addr) {
    unsigned int i;

    for(i = 0; i < 16; i++) {
        if(addr & (1 << (15-i))) {
            digital_write(_addr, HIGH);
        } else {
            digital_write(_addr, LOW);
        }

        digital_write(_ck, HIGH);
        digital_write(_ck, LOW);
    }

    digital_write(_addr, LOW);
}

void at28c256_write(unsigned short addr, unsigned char data) {
    // just to be safe, disable output
    digital_write(_oe, HIGH);

    // set the output address
    set_addr(addr);

    // write data
    pin_mode(_io0, OUTPUT);
    pin_mode(_io1, OUTPUT);
    pin_mode(_io2, OUTPUT);
    pin_mode(_io3, OUTPUT);
    pin_mode(_io4, OUTPUT);
    pin_mode(_io5, OUTPUT);
    pin_mode(_io6, OUTPUT);
    pin_mode(_io7, OUTPUT);

    digital_write(_io0, data & 1 ? HIGH : LOW);
    digital_write(_io1, data & (1<<1) ? HIGH : LOW);
    digital_write(_io2, data & (1<<2) ? HIGH : LOW);
    digital_write(_io3, data & (1<<3) ? HIGH : LOW);
    digital_write(_io4, data & (1<<4) ? HIGH : LOW);
    digital_write(_io5, data & (1<<5) ? HIGH : LOW);
    digital_write(_io6, data & (1<<6) ? HIGH : LOW);
    digital_write(_io7, data & (1<<7) ? HIGH : LOW);

    digital_write(_we, LOW);
    _delay_us(1); // min 100ns
    digital_write(_we, HIGH);
}

unsigned char at28c256_read(unsigned short addr) {
    // just to be safe, disable write
    digital_write(_we, HIGH);

    // set the output address
    set_addr(addr);

    // read data
    pin_mode(_io0, INPUT);
    pin_mode(_io1, INPUT);
    pin_mode(_io2, INPUT);
    pin_mode(_io3, INPUT);
    pin_mode(_io4, INPUT);
    pin_mode(_io5, INPUT);
    pin_mode(_io6, INPUT);
    pin_mode(_io7, INPUT);

    unsigned char data = 0;
    digital_write(_oe, LOW);
    data |= digital_read(_io0);
    data |= digital_read(_io1)<<1;
    data |= digital_read(_io2)<<2;
    data |= digital_read(_io3)<<3;
    data |= digital_read(_io4)<<4;
    data |= digital_read(_io5)<<5;
    data |= digital_read(_io6)<<6;
    data |= digital_read(_io7)<<7;
    digital_write(_oe, HIGH);

    return data;
}
