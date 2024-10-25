
#ifndef __PROC_H__
#define __PROC_H__

#include "ctrl_regs.h"
#include "rcv.h"
#include "xmt.h"

#define RT_ADDRESS      (0x1F << 11)
#define MSG_ERROR       (1    << 10)
#define INSTR_BIT       (1    << 1)
#define SERVICE_REQ     (1    << 5)
#define BCST_RCVD       (1    << 4)
#define BUSY            (1    << 3)
#define SUBSYS_FLAG     (1    << 2)
#define DYN_BUS_ACCEPT  (1    << 1)
#define TERMINAL_FLAG   (1    << 0)

#define WORD_COUNT_MASK (0x1F)

#define BROADCAST_MSG(data) ((data && RT_ADDR_MASK) == BROADCAST_ADDR)

#define RT_ADDR_MASK        (0xF800)
#define DIR_MASK            (0x0400)
#define SUB_ADDR_MASK       (0x03e0)
#define MODE_CODE_MASK      (0x041F)

#define BROADCAST_ADDR      (31<< 11)

#define MODE_CODE_ADDR0     (0 << 5)
#define MODE_CODE_ADDR1     (31<< 5)

#define COMMAND_WORD        (0x0)
#define DATA_WORD           (0x1)
#define STATUS_WORD         (0x0)

#define RCV_BASE_INDX   0
#define XMT_BASE_INDX   32
#define MODE_BASE_INDX  64

void msg_processor_unit();

#endif

