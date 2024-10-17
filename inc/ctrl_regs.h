
#ifndef __CONTROL_REGS_H__
#define __CONTROL_REGS_H__

#include "io.h"

#define CSR_BASE_ADDR 0x60000

// RW
#define CONTROL                                   0
#define CONTROL_GET()                             IORD(CSR_BASE_ADDR,CONTROL)
#define CONTROL_SET(data)                         IOWR(CSR_BASE_ADDR,CONTROL,data)

#define CONTROL_IRE_MASK                          (0x1)
#define CONTROL_IRE_OFST                          (7)
#define CONTROL_IRE_GET(data)                     GET_FIELD_VALUE(CONTROL_IRE,data)
#define CONTROL_IRE_SET(data)                     SET_FIELD_VALUE(CONTROL_IRE,data)

#define RT_MSG_PTR_TABLE_ADDR                     1
#define RT_MSG_PTR_TABLE_ADDR_GET()               IORD(CSR_BASE_ADDR,RT_MSG_PTR_TABLE_ADDR)
#define RT_MSG_PTR_TABLE_ADDR_SET(data)           IOWR(CSR_BASE_ADDR,RT_MSG_PTR_TABLE_ADDR,data)

#define BASIC_STATUS                              2
#define BASIC_STATUS_GET()                        IORD(CSR_BASE_ADDR,BASIC_STATUS)
#define BASIC_STATUS_SET(data)                    IOWR(CSR_BASE_ADDR,BASIC_STATUS,data)

#define BASIC_STATUS_ME_MASK                      (0x1)
#define BASIC_STATUS_ME_OFST                      (10)
#define BASIC_STATUS_ME_GET(data)                 GET_FIELD_VALUE(BASIC_STATUS_ME,data)
#define BASIC_STATUS_ME_SET(data)                 SET_FIELD_VALUE(BASIC_STATUS_ME,data)

#define BASIC_STATUS_RT_ADDR_MASK                 (0x1F)
#define BASIC_STATUS_RT_ADDR_OFST                 (11)
#define BASIC_STATUS_RT_ADDR_GET(data)            GET_FIELD_VALUE(BASIC_STATUS_RT_ADDR,data)
#define BASIC_STATUS_RT_ADDR_SET(data)            SET_FIELD_VALUE(BASIC_STATUS_RT_ADDR,data)

#define CONFIG_REG1                               9
#define CONFIG_REG1_GET()                         IORD(CSR_BASE_ADDR,CONFIG_REG1)
#define CONFIG_REG1_SET(data)                     IOWR(CSR_BASE_ADDR,CONFIG_REG1,data)

/*
#define INTERRUPT_MASKL_REG                     3
#define INTERRUPT_VECTORH_REG                   3
#define INTERRUPT_REQUESTH_REG                  3
#define INTERRUPT_VECTORL_REG                   4
#define AUX_VECTORH_REG                         4
#define CONFIG2H_REG                            4
#define RTC_HIGH_WORD_REG                       5
#define RTC_LOW_WORD_REG                        6
#define RTC_CONTROL_REG                         7
#define READ_FIFO_REG                           8
#define RESET_FIFO_REG                          8
#define BC_CUR_MJR_MNR_FRM_INDX_REG             10
#define MJR_FRM_A_ADDR_REG                      13
#define ASYNC_FRAME_ADDR_REG                    14
#define RESET_TERMINAL_REG                      15
#define MJR_FRM_B_ADDR_REG                      16
//#define RESERVED
#define ENCODER_STATUS_REG                      18
#define CONDITION_REG                           19
#define BCU_FRM_GAP_WORD_MTU_EOF_OPTIONS_REG    20
#define CONFIG3_REG                             21
#define MSG_MON_ADDRL_FILTER_REG                22
#define ENCODER_DATA_REG                        23
#define ENCODER_DATA_TX_REQ_REG                 24
#define ENCODER_CMD_TX_REQ_REG                  25
#define MSG_MON_ADDRH_FILTER_REG                26
#define BC_CUR_MNR_FRM_ADDR_REG                 27
#define CLEAR_REGISTER_27_REG                   27
#define MON_BLOCK_B_LAST_ADDR_REG               27
#define BC_CUR_MSG_ADDR_REG                     28
#define CLEAR_REGISTER_28_REG                   28
#define RT_LOG_PTR_TABLE_ADDR_REG               29
#define EXTERNAL_RTU_ADDR_BUFL_REG              30
#define BC_MU_IRQ_VECTOR_REG                    31
*/

#endif

