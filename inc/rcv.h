
#ifndef __RCV_H__
#define __RCV_H__

#include "ctrl_regs.h"
#include "mil_std.h"

typedef struct {
  uint16_t word;
  uint16_t status;
  uint16_t errors;
} rx_msg_info_t;

#define RX_MSG_TABLE_SIZE_MASK    (0x3F)
#define RX_MSG_TABLE_SIZE_OFST    (0)

#define RX_MSG_TABLE_INDX_MASK    (0x3F)
#define RX_MSG_TABLE_INDX_OFST    (8)

#define RX_MSG_TABLE_LOCK         (1<<7)
#define RX_MSG_TABLE_TIMESTAMP    (1<<14)
#define RX_MSG_TABLE_INDX_UPDATE  (1<<15)

#define RX_DATA_TABLE_OVW         (1<<5)
#define RX_DATA_TABLE_INVALID     (1<<6)
#define RX_DATA_TABLE_LOCK        (1<<7)
#define RX_DATA_TABLE_IRQ         (1<<12)
#define RX_DATA_TABLE_BCST        (1<<13)
#define RX_DATA_TABLE_UPDATE      (1<<15)

#endif

