
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

void rt_msg_processor();

#endif

