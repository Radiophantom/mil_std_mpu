
#ifndef __XMT_H__
#define __XMT_H__

#include "ctrl_regs.h"
#include "mil_std.h"

typedef struct {
  unsigned char   msg_type;
  unsigned short  data;
} tx_msg_info_t;

void send_tx_word(unsigned short* BASE_ADDR, tx_msg_info_t* msg_info);

#endif

