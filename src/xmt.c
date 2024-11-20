
#include "proc.h"
#include "xmt.h"

void transmit_fsm(){

  uint16_t* pointer_table_addr;
  uint16_t* msg_table_addr;
  uint16_t* data_table_addr;

  uint32_t timestamp;
  uint16_t data_table_size;
  uint16_t data_table_indx;

  int      broadcast;
  uint8_t  words_cnt;

  timestamp = get_timestamp_counter();

  if((rx_word.word_data & RT_ADDR_MASK) != BROADCAST_ADDR)
    // Ignore message and suppress response
    //return;
  else if((rx_word.word_data & RT_ADDR_MASK) != (BASIC_STATUS_GET() & RT_ADDR_MASK))
    // Ignore message and suppress response
    return;

  pointer_table_addr = (uint16_t*)(RT_MSG_PTR_TABLE_ADDR_GET()<<1)+XMT_BASE_INDX+((rx_word.word_data & SUB_ADDR_MASK)>>SUB_ADDR_OFST);
  if(*pointer_table_addr == 0x0)
    // Ignore message and suppress response
    return;

  msg_table_addr = (uint16_t*)(*pointer_table_addr << 1);

  msg_table_lock(msg_table_addr);

  data_table_size = (*msg_table_addr & MSG_TABLE_SIZE_MASK) >> MSG_TABLE_SIZE_OFST;
  if(data_table_size == 0x0){
    // TODO: Means virgin data set. So always should be minimum 1 data table if pointer is ON ???
    data_table_indx = 0;
  } else {
    data_table_indx = (*msg_table_addr & MSG_TABLE_INDX_MASK) >> MSG_TABLE_INDX_OFST;
  }

  data_table_indx++;
  if(data_table_indx > data_table_size){
    data_table_indx = 1;
  }

  data_table_addr = (uint16_t*)(*msg_table_addr << 1) + data_table_indx;

  data_table_lock(data_table_addr);

  broadcast = ((rx_word.word_data & RT_ADDR_MASK) == BROADCAST_ADDR);
  words_cnt = (rx_word.word_data & WORD_COUNT_MASK);

  if(words_cnt == 0)
    words_cnt = 32;

  response_gap(12);

  send_tx_word(0,STATUS_WORD);

  while(tx_word_empty() == 0){
    // NOP
  }

  if(SEND_TX_TIMESTAMP){
    send_tx_word(1,timestamp & 0xFFFF);
    while(tx_word_empty() == 0){
      // NOP
    }
    send_tx_word(1,timestamp >> 16);
    while(tx_word_empty() == 0){
      // NOP
    }
  }

  for(int i = 0; i < words_cnt;i++){
    send_tx_word(1,*(cmd_msg_table_addr+3+i));
    while(tx_word_empty() == 0){
      // NOP
    }
  }

  *data_table_addr = *data_table_addr & ~(DATA_TABLE_UPDATE);
  *data_table_addr = *data_table_addr | DATA_TABLE_UPDATE | (words_cnt & DATA_TABLE_WCNT);
  *msg_table_addr  = *msg_table_addr  | data_table_indx;
  data_table_unlock(data_table_addr);
  msg_table_unlock(msg_table_addr);

  return;
}

