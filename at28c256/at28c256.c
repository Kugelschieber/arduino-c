#include "at28c256.h"
#include "../ard/pins.h"

unsigned char _addrck, _addr;

void at28c256_init(unsigned char addrck, unsigned char addr) {
	pin_mode(addrck, OUTPUT);
	digital_write(addrck, LOW); // disable
	pin_mode(addr, OUTPUT);
	digital_write(addr, LOW); // disable
	
    _addrck = addrck;
	_addr = addr;
}

void at28c256_write(unsigned short addr, unsigned char data) {
    // set the address
    unsigned int i;

    for(i = 0; i < 16; i++) {
        if(addr & (1 << (15-i))) {
            digital_write(_addr, HIGH);
        } else {
            digital_write(_addr, LOW);
        }

        digital_write(_addrck, HIGH);
        digital_write(_addrck, LOW);
    }

    digital_write(_addr, LOW);

    // TODO write data
}
