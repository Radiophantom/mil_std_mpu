
#ifndef __XMT_H__
#define __XMT_H__

#include "ctrl_regs.h"
#include "mil_std.h"

void send_tx_word(uint16_t* BASE_ADDR, tx_msg_info_t* msg_info);

#endif

