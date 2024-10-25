
#include "xmt.h"

int tx_word_empty(){
  return (XMT_IRQ_VECTOR_TRS_GET(XMT_IRQ_VECTOR_GET()) == 0);
}

void send_tx_word(uint16_t cmd,uint16_t data){
  XMT_DATA_WORD_SET(data);
  XMT_DATA_STATUS_SET(XMT_DATA_STATUS_SYNC_C_SET(cmd)); 
  XMT_IRQ_VECTOR_SET(XMT_IRQ_VECTOR_TRS_SET(1));
}

void transmit_fsm(){

  int timestamp = get_timestamp_counter();

  lock_xmt_msg_table();

  uint16_t* rt_msg_table_addr   = (uint16_t*)RT_MSG_PTR_TABLE_ADDR_GET();
  uint16_t* cmd_msg_table_addr  = rt_msg_table_addr+64+(rx_msg_info.word & SUB_ADDR_MASK);

  int broadcast = BROADCAST_MSG(rx_msg_info.word);
  int words_cnt = (rx_msg_info.word & WORD_COUNT_MASK);

  if(broadcast)
    // Reset transaction
    return;

  if(words_cnt == 0)
    words_cnt = 32;

  response_gap();

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

  update_xmt_msg_table();

}

void update_xmt_msg_table(){
  // Set 'update' bit and 'words cnt'
  // Reset 'lock' bit
}

void lock_xmt_msg_table(){
  // Set 'lock' bit
}

