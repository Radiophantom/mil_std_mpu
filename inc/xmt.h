
#ifndef __XMT_H__
#define __XMT_H__

#include "ctrl_regs.h"
#include "mil_std.h"

typedef struct {
  uint8_t   msg_type;
  uint16_t  data;
} tx_msg_info_t;

void send_tx_word(uint16_t* BASE_ADDR, tx_msg_info_t* msg_info);

#endif

