
#include "proc.h"

void ERROR(){
  // Do nothing now
}

// FIXME: Not 'ns', but 'ticks' for debug
void response_gap(uint32_t ns){
  while(ns--){
    // NOP
  }
}

uint32_t get_timestamp_counter(){
  return 0x01234567;
}

void msg_table_lock(uint16_t* msg_table_addr){
  *msg_table_addr = (*msg_table_addr | MSG_TABLE_LOCK);
}

void msg_table_unlock(uint16_t* msg_table_addr){
  *msg_table_addr = (*msg_table_addr & ~(MSG_TABLE_LOCK));
}

void data_table_lock(uint16_t* data_table_addr){
  *data_table_addr = (*data_table_addr | DATA_TABLE_LOCK);
}

void data_table_unlock(uint16_t* data_table_addr){
  *data_table_addr = (*data_table_addr & ~(DATA_TABLE_LOCK));
};

int rx_word_empty(){
  return ((RCV_IRQ_VECTOR_GET() & RCV_IRQ_VECTOR_MSG_VALID) == 0);
}

// FIXME: Timeout in 'ticks', not 'ns' for debug purposes
// Return values: 0 - success
//                1 - timeout error
int get_rx_word(rx_word_t* rx_word,uint32_t timeout_ns){
  while(rx_word_empty()){
    if(timeout_ns-- == 0)
      return TIMEOUT_ERROR;
  }
  rx_word -> word_data    = RCV_DATA_WORD_GET();
  rx_word -> word_status  = RCV_DATA_STATUS_GET();
  rx_word -> word_errors  = RCV_DATA_ERRORS_GET();
  RCV_IRQ_VECTOR_SET(RCV_IRQ_VECTOR_MSG_VALID);
  return SUCCESS;
}

int tx_word_empty(){
  return ((XMT_CONTROL_GET() & XMT_CONTROL_BUSY) == 0);
}

void send_tx_word(uint16_t cmd,uint16_t data){
  uint32_t timeout_ns = 1000000;
  XMT_DATA_WORD_SET(data);
  if(cmd)
    XMT_DATA_STATUS_SET(XMT_DATA_STATUS_SYNC_C);
  else
    XMT_DATA_STATUS_SET(0);
  XMT_DATA_SEND_SET(XMT_DATA_SEND_STB);
  while(!tx_word_empty()){
    if(timeout_ns-- == 0)
      break;
  }
}

