#ifndef NRF24L01_H_
#define NRF24L01_H_

#define CONFIG          0x00
#define MASK_RX_DR      6
#define MASK_TX_DS      5
#define MASK_MAX_RT     4
#define EN_CRC          3
#define CRCO            2
#define PWR_UP          1
#define PRIM_RX         0

#define EN_AA           0x01
#define ENAA_P5         5
#define ENAA_P4         4
#define ENAA_P3         3
#define ENAA_P2         2
#define ENAA_P1         1
#define ENAA_P0         0

#define EN_RXADDR       0x02
#define ERX_P5          5
#define ERX_P4          4
#define ERX_P3          3
#define ERX_P2          2
#define ERX_P1          1
#define ERX_P0          0

#define SETUP_AW        0x03
#define AW              0 // 2 bits

#define SETUP_RETR      0x04
#define ARD             4 // 4 bits
#define ARC             0 // 4 bits

#define RF_CH_REG       0x05
#define RF_CH           0 // 7 bits
#define RF_CH_MASK      0x7F

#define RF_SETUP        0x06
#define CONT_WAVE       7
#define RF_DR_LOW       5
#define PLL_LOCK        4
#define RF_DR_HIGH      3
#define RF_PWR          1 // 2 bits

#define STATUS          0x07
#define RX_DR           6
#define TX_DS           5
#define MAX_RT          4
#define RX_P_NO         1 // 3 bits
#define STATUS_TX_FULL  0

#define OBSERVE_TX      0x08
#define PLOS_CNT        4 // 4 bits
#define ARC_CNT         0 // 4 bits

#define RPD_REG         0x09
#define RPD             0

#define RX_ADDR_P0      0x0A // 5 bytes
#define RX_ADDR_P1      0x0B // 5 bytes
#define RX_ADDR_P2      0x0C // 1 byte
#define RX_ADDR_P3      0x0D // 1 byte
#define RX_ADDR_P4      0x0E // 1 byte
#define RX_ADDR_P5      0x0F // 1 byte

#define TX_ADDR         0x10 // 5 bytes

#define RX_PW_P0_REG    0x11
#define RX_PW_P0        0 // 6 bits
#define RX_PW_P1_REG    0x12
#define RX_PW_P1        0 // 6 bits
#define RX_PW_P2_REG    0x13
#define RX_PW_P2        0 // 6 bits
#define RX_PW_P3_REG    0x14
#define RX_PW_P3        0 // 6 bits
#define RX_PW_P4_REG    0x15
#define RX_PW_P4        0 // 6 bits
#define RX_PW_P5_REG    0x16
#define RX_PW_P5        0 // 6 bits
#define RX_PW_MASK      0x3F

#define FIFO_STATUS     0x17
#define TX_REUSE        6
#define TX_FULL         5
#define TX_EMPTY        4
#define RX_FULL         1
#define RX_EMPTY        0

#define DYNPD           0x1C
#define DPL_P5          5
#define DPL_P4          4
#define DPL_P3          3
#define DPL_P2          2
#define DPL_P1          1
#define DPL_P0          0

#define FEATURE         0x1D
#define EN_DPL          2
#define EN_ACK_PAY      1
#define EN_DYN_ACK      0

#define R_REGISTER      0x00
#define W_REGISTER      0x20
#define REG_MASK        0x1F
#define R_RX_PAYLOAD    0x61
#define W_TX_PAYLOAD    0xA0
#define FLUSH_TX        0xE1
#define FLUSH_RX        0xE2
#define REUSE_TX_PL     0xE3
#define R_RX_PL_WID     0x60
#define W_ACK_PAYLOAD   0xA8
#define W_ACK_PAYLOAD_MASK 0x07
#define PIPE_0          0x00
#define PIPE_1          0x01
#define PIPE_2          0x02
#define PIPE_3          0x03
#define PIPE_4          0x04
#define PIPE_5          0x05
#define W_TX_PAYLOAD_NOACK 0xB0
#define NOP             0xFF

// TODO

#endif
