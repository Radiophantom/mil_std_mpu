
#ifndef __RCV_H__
#define __RCV_H__

#include "ctrl_regs.h"

// RW
#define CONTROL_REG                   0
#define IORD_CONTROL_REG(base)        IORD(base,CONTROL_REG)
#define IOWR_CONTROL_REG(base,data)   IOWR(base,CONTROL_REG,data)

#define CONTROL_REG_VALID_MASK        (0x1)
#define CONTROL_REG_VALID_OFST        (0)
#define CONTROL_REG_VALID_GET(data)   _GET_BITS(data,CONTROL_REG_VALID_MASK,CONTROL_REG_VALID_OFST)

#define CONTROL_REG_SYNC_MASK         (0x1)
#define CONTROL_REG_SYNC_OFST         (1)
#define CONTROL_REG_SYNC_GET(data)    _GET_BITS(data,CONTROL_REG_SYNC_MASK,CONTROL_REG_SYNC_OFST)

// RO
#define DATA_REG
#define IORD_DATA_REG(base)           IORD(base,DATA_REG)

// RO
#define TIMESTAMPL_REG
#define IORD_TIMESTAMPL_REG(base)     IORD(base,TIMESTAMPL_REG)

// RO
#define TIMESTAMPH_REG 
#define IORD_TIMESTAMPH_REG(base)     IORD(base,TIMESTAMPH_REG)

// RO
#define ERRORS_REG
#define IORD_ERRORS_REG(base)         IORD(base,ERRORS_REG)

#define ERRORS_REG_PARITY_MASK        (0x1)
#define ERRORS_REG_PARITY_OFST        (0)
#define ERRORS_REG_PARITY_GET(data)   _GET_BITS(data,ERRORS_REG_PARITY_MASK,ERRORS_REG_PARITY_OFST)

#endif

