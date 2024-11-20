
#ifndef __MIL_STD_H__
#define __MIL_STD_H__

#include "io.h"

#define MIL_STD_BASE_ADDR 0x20000

// RW
#define RCV_CONTROL                       0
#define RCV_CONTROL_GET()                 IORD(MIL_STD_BASE_ADDR,RCV_CONTROL)
#define RCV_CONTROL_SET(data)             IOWR(MIL_STD_BASE_ADDR,RCV_CONTROL,data)

#define RCV_CONTROL_ENABLE                (1<<0)
#define RCV_CONTROL_BUSY                  (1<<15)

//#define RCV_CONTROL_ENABLE_MASK           (0x1)
//#define RCV_CONTROL_ENABLE_OFST           (0)
//#define RCV_CONTROL_ENABLE_GET(data)      GET_FIELD_VALUE(RCV_CONTROL_ENABLE,data)
//#define RCV_CONTROL_ENABLE_SET(data)      SET_FIELD_VALUE(RCV_CONTROL_ENABLE,data)
//
//#define RCV_CONTROL_BUSY_MASK             (0x1)
//#define RCV_CONTROL_BUSY_OFST             (15)
//#define RCV_CONTROL_BUSY_GET(data)        GET_FIELD_VALUE(RCV_CONTROL_BUSY,data)
//#define RCV_CONTROL_BUSY_SET(data)        SET_FIELD_VALUE(RCV_CONTROL_BUSY,data)

// RW
#define RCV_IRQ_ENABLE                    1
#define RCV_IRQ_ENABLE_GET()              IORD(MIL_STD_BASE_ADDR,RCV_IRQ_ENABLE)
#define RCV_IRQ_ENABLE_SET(data)          IOWR(MIL_STD_BASE_ADDR,RCV_IRQ_ENABLE,data)

// RW
#define RCV_IRQ_VECTOR                    2
#define RCV_IRQ_VECTOR_GET()              IORD(MIL_STD_BASE_ADDR,RCV_IRQ_VECTOR)
#define RCV_IRQ_VECTOR_SET(data)          IOWR(MIL_STD_BASE_ADDR,RCV_IRQ_VECTOR,data)

#define RCV_IRQ_VECTOR_MSG_VALID          (1<<0)

//#define RCV_IRQ_VECTOR_MSG_VALID_MASK     (0x1)
//#define RCV_IRQ_VECTOR_MSG_VALID_OFST     (1)
//#define RCV_IRQ_VECTOR_MSG_VALID_GET(data)GET_FIELD_VALUE(RCV_CONTROL_IRQ_EN,data)
//#define RCV_IRQ_VECTOR_MSG_VALID_SET(data)SET_FIELD_VALUE(RCV_CONTROL_IRQ_EN,data)

// RW
#define RCV_DATA_WORD                     3
#define RCV_DATA_WORD_GET()               IORD(MIL_STD_BASE_ADDR,RCV_DATA_WORD)
#define RCV_DATA_WORD_SET(data)           IOWR(MIL_STD_BASE_ADDR,RCV_DATA_WORD,data)

// RW
#define RCV_DATA_STATUS                   4
#define RCV_DATA_STATUS_GET()             IORD(MIL_STD_BASE_ADDR,RCV_DATA_STATUS)
#define RCV_DATA_STATUS_SET(data)         IOWR(MIL_STD_BASE_ADDR,RCV_DATA_STATUS,data)

#define RCV_DATA_STATUS_SYNC_C            (1<<0)

//#define RCV_DATA_STATUS_SYNC_C_MASK       (0x1)
//#define RCV_DATA_STATUS_SYNC_C_OFST       (0)
//#define RCV_DATA_STATUS_SYNC_C_GET(data)  GET_FIELD_VALUE(RCV_DATA_STATUS_SYNC_C,data)
//#define RCV_DATA_STATUS_SYNC_C_SET(data)  SET_FIELD_VALUE(RCV_DATA_STATUS_SYNC_C,data)

// RW
#define RCV_DATA_ERRORS                   5
#define RCV_DATA_ERRORS_GET()             IORD(MIL_STD_BASE_ADDR,RCV_DATA_ERRORS)
#define RCV_DATA_ERRORS_SET(data)         IOWR(MIL_STD_BASE_ADDR,RCV_DATA_ERRORS,data)

#define RCV_DATA_ERRORS_PARITY            (1<<0)

//#define RCV_DATA_ERRORS_PARITY_MASK       (0x1)
//#define RCV_DATA_ERRORS_PARITY_OFST       (0)
//#define RCV_DATA_ERRORS_PARITY_GET(data)  GET_FIELD_VALUE(RCV_DATA_ERRORS_PARITY,data)
//#define RCV_DATA_ERRORS_PARITY_SET(data)  SET_FIELD_VALUE(RCV_DATA_ERRORS_PARITY,data)

// RW
#define XMT_CONTROL                       6
#define XMT_CONTROL_GET()                 IORD(MIL_STD_BASE_ADDR,XMT_CONTROL)
#define XMT_CONTROL_SET(data)             IOWR(MIL_STD_BASE_ADDR,XMT_CONTROL,data)

#define XMT_CONTROL_ENABLE                (1<<0)
#define XMT_CONTROL_BUSY                  (1<<15)

//#define XMT_CONTROL_ENABLE_MASK           (0x1)
//#define XMT_CONTROL_ENABLE_OFST           (0)
//#define XMT_CONTROL_ENABLE_GET(data)      GET_FIELD_VALUE(XMT_CONTROL_ENABLE,data)
//#define XMT_CONTROL_ENABLE_SET(data)      SET_FIELD_VALUE(XMT_CONTROL_ENABLE,data)
//
//#define XMT_CONTROL_BUSY_MASK             (0x1)
//#define XMT_CONTROL_BUSY_OFST             (15)
//#define XMT_CONTROL_BUSY_GET(data)        GET_FIELD_VALUE(XMT_CONTROL_BUSY,data)
//#define XMT_CONTROL_BUSY_SET(data)        SET_FIELD_VALUE(XMT_CONTROL_BUSY,data)

// RW
#define XMT_IRQ_ENABLE                    7
#define XMT_IRQ_ENABLE_GET()              IORD(MIL_STD_BASE_ADDR,XMT_IRQ_ENABLE)
#define XMT_IRQ_ENABLE_SET(data)          IOWR(MIL_STD_BASE_ADDR,XMT_IRQ_ENABLE,data)

// RW
#define XMT_IRQ_VECTOR                    8
#define XMT_IRQ_VECTOR_GET()              IORD(MIL_STD_BASE_ADDR,XMT_IRQ_VECTOR)
#define XMT_IRQ_VECTOR_SET(data)          IOWR(MIL_STD_BASE_ADDR,XMT_IRQ_VECTOR,data)

// RW
#define XMT_DATA_SEND                     9
#define XMT_DATA_SEND_GET()               IORD(MIL_STD_BASE_ADDR,XMT_DATA_WORD)
#define XMT_DATA_SEND_SET(data)           IOWR(MIL_STD_BASE_ADDR,XMT_DATA_WORD,data)

#define XMT_DATA_SEND_STB                 (1<<0)

//#define XMT_DATA_SEND_STB_MASK            (0x1)
//#define XMT_DATA_SEND_STB_OFST            (0)
//#define XMT_DATA_SEND_STB_GET(data)       GET_FIELD_VALUE(XMT_DATA_SEND_STB,data)
//#define XMT_DATA_SEND_STB_SET(data)       SET_FIELD_VALUE(XMT_DATA_SEND_STB,data)

// RW
#define XMT_DATA_WORD                     10
#define XMT_DATA_WORD_GET()               IORD(MIL_STD_BASE_ADDR,XMT_DATA_WORD)
#define XMT_DATA_WORD_SET(data)           IOWR(MIL_STD_BASE_ADDR,XMT_DATA_WORD,data)

// RW
#define XMT_DATA_STATUS                   11
#define XMT_DATA_STATUS_GET()             IORD(MIL_STD_BASE_ADDR,XMT_DATA_STATUS)
#define XMT_DATA_STATUS_SET(data)         IOWR(MIL_STD_BASE_ADDR,XMT_DATA_STATUS,data)

#define XMT_DATA_STATUS_SYNC_C            (1<<0)

//#define XMT_DATA_STATUS_SYNC_C_MASK       (0x1)
//#define XMT_DATA_STATUS_SYNC_C_OFST       (0)
//#define XMT_DATA_STATUS_SYNC_C_GET(data)  GET_FIELD_VALUE(XMT_DATA_STATUS_SYNC_C,data)
//#define XMT_DATA_STATUS_SYNC_C_SET(data)  SET_FIELD_VALUE(XMT_DATA_STATUS_SYNC_C,data)

#endif

