
#ifndef __MIL_STD_H__
#define __MIL_STD_H__

#include "io.h"

#define MIL_STD_BASE_ADDR 0x20000

// RW
#define RCV_CONTROL                       0
#define RCV_CONTROL_GET()                 IORD(MIL_STD_BASE_ADDR,RCV_CONTROL)
#define RCV_CONTROL_SET(data)             IOWR(MIL_STD_BASE_ADDR,RCV_CONTROL,data)

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
#define RCV_IRQ_VECTOR_GET()              IORD(MIL_STD_BASE_ADDR,RCV_IRQ_VECTOR)
#define RCV_IRQ_VECTOR_SET(data)          IOWR(MIL_STD_BASE_ADDR,RCV_IRQ_VECTOR,data)

#define RCV_IRQ_VECTOR_RCV_MASK           (0x1)
#define RCV_IRQ_VECTOR_RCV_OFST           (0)
#define RCV_IRQ_VECTOR_RCV_GET(data)      GET_FIELD_VALUE(RCV_IRQ_VECTOR_RCV,data)
#define RCV_IRQ_VECTOR_RCV_SET(data)      SET_FIELD_VALUE(RCV_IRQ_VECTOR_RCV,data)

// RW
#define RCV_DATA_WORD                     2
#define RCV_DATA_WORD_GET()               IORD(MIL_STD_BASE_ADDR,RCV_DATA_WORD)
#define RCV_DATA_WORD_SET(data)           IOWR(MIL_STD_BASE_ADDR,RCV_DATA_WORD,data)

// RW
#define RCV_DATA_STATUS                   3
#define RCV_DATA_STATUS_GET()             IORD(MIL_STD_BASE_ADDR,RCV_DATA_STATUS)
#define RCV_DATA_STATUS_SET(data)         IOWR(MIL_STD_BASE_ADDR,RCV_DATA_STATUS,data)

#define RCV_DATA_STATUS_SYNC_C_MASK       (0x1)
#define RCV_DATA_STATUS_SYNC_C_OFST       (0)
#define RCV_DATA_STATUS_SYNC_C_GET(data)  GET_FIELD_VALUE(RCV_DATA_STATUS_SYNC_C,data)
#define RCV_DATA_STATUS_SYNC_C_SET(data)  SET_FIELD_VALUE(RCV_DATA_STATUS_SYNC_C,data)

// RW
#define RCV_DATA_ERRORS                   4
#define RCV_DATA_ERRORS_GET()             IORD(MIL_STD_BASE_ADDR,RCV_DATA_ERRORS)
#define RCV_DATA_ERRORS_SET(data)         IOWR(MIL_STD_BASE_ADDR,RCV_DATA_ERRORS,data)

#define RCV_DATA_ERRORS_PARITY_MASK       (0x1)
#define RCV_DATA_ERRORS_PARITY_OFST       (0)
#define RCV_DATA_ERRORS_PARITY_GET(data)  GET_FIELD_VALUE(RCV_DATA_ERRORS_PARITY,data)
#define RCV_DATA_ERRORS_PARITY_SET(data)  SET_FIELD_VALUE(RCV_DATA_ERRORS_PARITY,data)

// RW
#define XMT_CONTROL                       5
#define XMT_CONTROL_GET()                 IORD(MIL_STD_BASE_ADDR,XMT_CONTROL)
#define XMT_CONTROL_SET(data)             IOWR(MIL_STD_BASE_ADDR,XMT_CONTROL,data)

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
#define XMT_CONTROL_BUSY_OFST             (15)
#define XMT_CONTROL_BUSY_GET(data)        GET_FIELD_VALUE(XMT_CONTROL_BUSY,data)
#define XMT_CONTROL_BUSY_SET(data)        SET_FIELD_VALUE(XMT_CONTROL_BUSY,data)

// RW
#define XMT_IRQ_VECTOR                    6
#define XMT_IRQ_VECTOR_GET()              IORD(MIL_STD_BASE_ADDR,XMT_IRQ_VECTOR)
#define XMT_IRQ_VECTOR_SET(data)          IOWR(MIL_STD_BASE_ADDR,XMT_IRQ_VECTOR,data)

#define XMT_IRQ_VECTOR_TRS_MASK           (0x1)
#define XMT_IRQ_VECTOR_TRS_OFST           (0)
#define XMT_IRQ_VECTOR_TRS_GET(data)      GET_FIELD_VALUE(XMT_IRQ_VECTOR_TRS,data)
#define XMT_IRQ_VECTOR_TRS_SET(data)      SET_FIELD_VALUE(XMT_IRQ_VECTOR_TRS,data)

// RW
#define XMT_DATA_WORD                     7
#define XMT_DATA_WORD_GET()               IORD(MIL_STD_BASE_ADDR,XMT_DATA_WORD)
#define XMT_DATA_WORD_SET(data)           IOWR(MIL_STD_BASE_ADDR,XMT_DATA_WORD,data)

// RW
#define XMT_DATA_STATUS                   8
#define XMT_DATA_STATUS_GET()             IORD(MIL_STD_BASE_ADDR,XMT_DATA_STATUS)
#define XMT_DATA_STATUS_SET(data)         IOWR(MIL_STD_BASE_ADDR,XMT_DATA_STATUS,data)

#define XMT_DATA_STATUS_SYNC_C_MASK       (0x1)
#define XMT_DATA_STATUS_SYNC_C_OFST       (0)
#define XMT_DATA_STATUS_SYNC_C_GET(data)  GET_FIELD_VALUE(XMT_DATA_STATUS_SYNC_C,data)
#define XMT_DATA_STATUS_SYNC_C_SET(data)  SET_FIELD_VALUE(XMT_DATA_STATUS_SYNC_C,data)

#endif

