# Arduino C

Programming the Arduino in pure C on Linux.

## Requirements

* arvdude
* arv-gcc
* avr-libc

## Compile and upload

Run using the following command (example port):

```
sudo ./compile.sh /dev/ttyUSB0
```

The port can be found by looking inside `/dev`, the system file `ll /sys/class/tty/ttyUSB*`, or by running `lsusb`.
