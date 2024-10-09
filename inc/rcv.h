
#ifndef __RCV_H__
#define __RCV_H__

#include "ctrl_regs.h"

// RW
#define RCV_CONTROL_                      0
#define RCV_CONTROL_GET(base)             IORD(base,RCV_CONTROL)
#define RCV_CONTROL_SET(base,data)        IOWR(base,RCV_CONTROL,data)

#define RCV_CONTROL_ENABLE_MASK           (0x1)
#define RCV_CONTROL_ENABLE_OFST           (0)
#define RCV_CONTROL_ENABLE_GET(data)      GET_FIELD_VALUE(RCV_CONTROL_ENABLE,data)
#define RCV_CONTROL_ENABLE_SET(data)      SET_FIELD_VALUE(RCV_CONTROL_ENABLE,data)

#define RCV_CONTROL_IRQ_EN_MASK           (0x1)
#define RCV_CONTROL_IRQ_EN_OFST           (1)
#define RCV_CONTROL_IRQ_EN_GET(data)      GET_FIELD_VALUE(RCV_CONTROL_IRQ_EN,data)
#define RCV_CONTROL_IRQ_EN_SET(data)      SET_FIELD_VALUE(RCV_CONTROL_IRQ_EN,data)

#define RCV_CONTROL_BUSY_MASK             (0x1)
#define RCV_CONTROL_BUSY_OFST             (15)
#define RCV_CONTROL_BUSY_GET(data)        GET_FIELD_VALUE(RCV_CONTROL_BUSY,data)
#define RCV_CONTROL_BUSY_SET(data)        SET_FIELD_VALUE(RCV_CONTROL_BUSY,data)

// RW
#define RCV_IRQ_VECTOR                    1
#define RCV_IRQ_VECTOR_GET(base)          IORD(base,RCV_IRQ_VECTOR)
#define RCV_IRQ_VECTOR_SET(base,data)     IOWR(base,RCV_IRQ_VECTOR,data)

#define RCV_IRQ_VECTOR_RCV_MASK           (0x1)
#define RCV_IRQ_VECTOR_RCV_OFST           (0)
#define RCV_IRQ_VECTOR_RCV_GET(data)      GET_FIELD_VALUE(RCV_IRQ_VECTOR_RCV,data)
#define RCV_IRQ_VECTOR_RCV_SET(data)      SET_FIELD_VALUE(RCV_IRQ_VECTOR_RCV,data)

// RW
#define RCV_DATA_WORD                     2
#define RCV_DATA_WORD_GET(base)           IORD(base,RCV_DATA_WORD)
#define RCV_DATA_WORD_SET(base,data)      IOWR(base,RCV_DATA_WORD,data)

// RW
#define RCV_DATA_STATUS                   3
#define RCV_DATA_STATUS_GET(base)         IORD(base,RCV_DATA_STATUS)
#define RCV_DATA_STATUS_SET(base,data)    IOWR(base,RCV_DATA_STATUS,data)

#define RCV_DATA_STATUS_SYNC_C_MASK       (0x1)
#define RCV_DATA_STATUS_SYNC_C_OFST       (0)
#define RCV_DATA_STATUS_SYNC_C_GET(data)  GET_FIELD_VALUE(RCV_DATA_STATUS_SYNC_C,data)
#define RCV_DATA_STATUS_SYNC_C_SET(data)  SET_FIELD_VALUE(RCV_DATA_STATUS_SYNC_C,data)

// RW
#define RCV_DATA_ERRORS                   4
#define RCV_DATA_ERRORS_GET(base)         IORD(base,RCV_DATA_ERRORS)
#define RCV_DATA_ERRORS_SET(base,data)    IOWR(base,RCV_DATA_ERRORS,data)

#define RCV_DATA_ERRORS_PARITY_MASK       (0x1)
#define RCV_DATA_ERRORS_PARITY_OFST       (0)
#define RCV_DATA_ERRORS_PARITY_GET(data)  GET_FIELD_VALUE(RCV_DATA_ERRORS_PARITY,data)
#define RCV_DATA_ERRORS_PARITY_SET(data)  SET_FIELD_VALUE(RCV_DATA_ERRORS_PARITY,data)

// RW
#define XMT_CONTROL                       5
#define XMT_CONTROL_GET(base)             IORD(base,XMT_CONTROL)
#define XMT_CONTROL_SET(base,data)        IOWR(base,XMT_CONTROL,data)

#define XMT_CONTROL_ENABLE_MASK           (0x1)
#define XMT_CONTROL_ENABLE_OFST           (0)
#define XMT_CONTROL_ENABLE_GET(data)      GET_FIELD_VALUE( data)
#define XMT_CONTROL_ENABLE_SET(data)      SET_FIELD_VALUE( data)

#define XMT_CONTROL_IRQ_EN_MASK           (0x1)
#define XMT_CONTROL_IRQ_EN_OFST           (1)
#define XMT_CONTROL_IRQ_EN_GET(data)      GET_FIELD_VALUE(XMT_CONTROL_IRQ_EN,data)
#define XMT_CONTROL_IRQ_EN_SET(data)      SET_FIELD_VALUE(XMT_CONTROL_IRQ_EN,data)

#define XMT_CONTROL_SEND_MASK             (0x1)
#define XMT_CONTROL_SEND_OFST             (2)
#define XMT_CONTROL_SEND_GET(data)        GET_FIELD_VALUE(XMT_CONTROL_SEND,data)
#define XMT_CONTROL_SEND_SET(data)        SET_FIELD_VALUE(XMT_CONTROL_SEND,data)

#define XMT_CONTROL_BUSY_MASK             (0x1)
#define XMT_CONTROL_BUSY_OFST             (3)
#define XMT_CONTROL_BUSY_GET(data)        GET_FIELD_VALUE(XMT_CONTROL_BUSY,data)
#define XMT_CONTROL_BUSY_SET(data)        SET_FIELD_VALUE(XMT_CONTROL_BUSY,data)

// RW
#define XMT_IRQ_VECTOR                    6
#define XMT_IRQ_VECTOR_GET(base)          IORD(base,XMT_IRQ_VECTOR)
#define XMT_IRQ_VECTOR_SET(base,data)     IOWR(base,XMT_IRQ_VECTOR,data)

#define XMT_IRQ_VECTOR_TRS_MASK           (0x1)
#define XMT_IRQ_VECTOR_TRS_OFST           (0)
#define XMT_IRQ_VECTOR_TRS_GET(data)      GET_FIELD_VALUE(XMT_IRQ_VECTOR_TRS,data)
#define XMT_IRQ_VECTOR_TRS_SET(data)      SET_FIELD_VALUE(XMT_IRQ_VECTOR_TRS,data)

// RW
#define XMT_DATA_WORD                     7
#define XMT_DATA_WORD_GET(base)           IORD(base,XMT_DATA_WORD)
#define XMT_DATA_WORD_SET(base,data)      IOWR(base,XMT_DATA_WORD,data)

// RW
#define XMT_DATA_STATUS                   8
#define XMT_DATA_STATUS_GET(base)         IORD(base,XMT_DATA_STATUS)
#define XMT_DATA_STATUS_SET(base,data)    IOWR(base,XMT_DATA_STATUS,data)

#define XMT_DATA_STATUS_SYNC_C_MASK       (0x1)
#define XMT_DATA_STATUS_SYNC_C_OFST       (0)
#define XMT_DATA_STATUS_SYNC_C_GET(data)  GET_FIELD_VALUE(XMT_DATA_STATUS_SYNC_C,data)
#define XMT_DATA_STATUS_SYNC_C_SET(data)  SET_FIELD_VALUE(XMT_DATA_STATUS_SYNC_C,data)

//------------------------------------------------------------------------------
// OLD VERSION
//------------------------------------------------------------------------------
//
//// RW
//#define CONTROL_REG                   0
//#define IORD_CONTROL_REG(base)        IORD(base,CONTROL_REG)
//#define IOWR_CONTROL_REG(base,data)   IOWR(base,CONTROL_REG,data)
//
//#define CONTROL_REG_VALID_MASK        (0x1)
//#define CONTROL_REG_VALID_OFST        (0)
//#define CONTROL_REG_VALID_GET(data)   _GET_BITS(data,CONTROL_REG_VALID_MASK,CONTROL_REG_VALID_OFST)
//
//#define CONTROL_REG_SYNC_MASK         (0x1)
//#define CONTROL_REG_SYNC_OFST         (1)
//#define CONTROL_REG_SYNC_GET(data)    _GET_BITS(data,CONTROL_REG_SYNC_MASK,CONTROL_REG_SYNC_OFST)
//
//// RO
//#define DATA_REG
//#define IORD_DATA_REG(base)           IORD(base,DATA_REG)
//
//// RO
//#define TIMESTAMPL_REG
//#define IORD_TIMESTAMPL_REG(base)     IORD(base,TIMESTAMPL_REG)
//
//// RO
//#define TIMESTAMPH_REG 
//#define IORD_TIMESTAMPH_REG(base)     IORD(base,TIMESTAMPH_REG)
//
//// RO
//#define ERRORS_REG
//#define IORD_ERRORS_REG(base)         IORD(base,ERRORS_REG)
//
//#define ERRORS_REG_PARITY_MASK        (0x1)
//#define ERRORS_REG_PARITY_OFST        (0)
//#define ERRORS_REG_PARITY_GET(data)   _GET_BITS(data,ERRORS_REG_PARITY_MASK,ERRORS_REG_PARITY_OFST)

#endif

