#ifndef NRF24L01_H_
#define NRF24L01_H_

#define CONFIG      0x00
#define MASK_RX_DR  6
#define MASK_TX_DS  5
#define MASK_MAX_RT 4
#define EN_CRC      3
#define CRCO        2
#define PWR_UP      1
#define PRIM_RX     0

#define STATUS      0x07
#define RX_DR       6
#define TX_DS       5
#define MAX_RT      4
#define RX_P_NO     3 // 3 bits
#define TX_FULL     0

#define R_REGISTER  0x00
#define W_REGISTER  0x20
#define REG_MASK    0x1f

// TODO

#endif
