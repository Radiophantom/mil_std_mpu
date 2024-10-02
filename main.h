
#define IDLE_S
#define RECIEVE_DATA_S
#define RECIEVE_MODE_CODE_S
#define TRANSMIT_DATA_S
#define TRANSMIT_MODE_CODE_S

#define RD_MSG_DATA       *(short unsigned*)(RCV_MSG_DATA_REG)
#define RD_MSG_STATUS     *(short unsigned*)(RCV_MSG_STAT_REG)
#define RD_MSG_TIME_TAGL  *(short unsigned*)(RCV_MSG_TIME_TAGL)
#define RD_MSG_TIME_TAGH  *(short unsigned*)(RCV_MSG_TIME_TAGH)

