
#ifndef __PROC_H__
#define __PROC_H__

#include "stdint.h"
#include "ctrl_regs.h"
#include "mil_std.h"

#define SUCCESS         0
#define TIMEOUT_ERROR   1

typedef struct {
  uint16_t  word_data;
  uint16_t  word_status;
  uint16_t  word_errors;
} rx_word_t;

typedef struct {
  uint16_t  word_type;
  uint16_t  word_data;
} tx_word_t;

// Receive routines
int rx_word_empty();
int get_rx_word(rx_word_t* data_info,uint32_t timeout_ns);
void receive_msg(rx_word_t* rx_word);

// Transmit routines
int tx_word_empty();
void send_tx_word(uint16_t cmd,uint16_t data);
void transmit_msg(rx_word_t* rx_word);

// Mode code routines
void mode_code_msg(rx_word_t* rx_word);

// Processing routines
void msg_table_lock(uint16_t* msg_table_addr);
void msg_table_unlock(uint16_t* msg_table_addr);
void data_table_lock(uint16_t* data_table_addr);
void data_table_unlock(uint16_t* data_table_addr);

uint32_t get_timestamp_counter();
void response_gap(uint32_t ns);
void ERROR();

#define MSG_TABLE_SIZE_OFST    (0)
#define MSG_TABLE_INDEX_OFST   (8)

#define MSG_TABLE_SIZE         (0x3F<<0)
#define MSG_TABLE_LOCK         (0x01<<7)
#define MSG_TABLE_INDEX        (0x3F<<8)
#define MSG_TABLE_TIME_TAG     (0x01<<14)
#define MSG_TABLE_INDEX_UPDATE (0x01<<15)

#define DATA_TABLE_WCNT        (0x1F<<0)
#define DATA_TABLE_OVW         (0x01<<5)
#define DATA_TABLE_INVALID     (0x01<<6)
#define DATA_TABLE_LOCK        (0x01<<7)
#define DATA_TABLE_IRQ         (0x01<<12)
#define DATA_TABLE_BCST        (0x01<<13)
#define DATA_TABLE_UPDATE      (0x01<<15)

// STATUS WORD layout
#define RT_ADDRESS      (0x1F<< 11)
#define MSG_ERROR       (0x01<< 10)
#define INSTR_BIT       (0x01<< 1) // Why index 1 - check!
#define SERVICE_REQ     (0x01<< 5)
#define BCST_RCVD       (0x01<< 4)
#define BUSY            (0x01<< 3)
#define SUBSYS_FLAG     (0x01<< 2)
#define DYN_BUS_ACCEPT  (0x01<< 1)
#define TERMINAL_FLAG   (0x01<< 0)

// MIL-STD WORD layout
#define RT_ADDR_MASK        (0xF800)
#define DIR_MASK            (0x0400)
#define SUB_ADDR_MASK       (0x03e0)
#define MODE_CODE_MASK      (0x041F)
#define WORD_COUNT_MASK     (0x001F)
#define SUB_ADDR_OFST       (5)

#define BROADCAST_ADDR      (31<<11)

#define MODE_CODE_ADDR0     ( 0<<SUB_ADDR_OFST)
#define MODE_CODE_ADDR1     (31<<SUB_ADDR_OFST)

#define COMMAND_WORD        (0x0)
#define DATA_WORD           (0x1)

#define RCV_BASE_INDX   0
#define XMT_BASE_INDX   32
#define MODE_BASE_INDX  64

#endif

