
#include "rcv.h"

#define SUCCESS       0
#define TIMEOUT_ERROR 1

int rx_word_empty(){
  return (RCV_IRQ_VECTOR_RCV_GET(RCV_IRQ_VECTOR_GET()) == 0);
}

// FIXME: Timeout in 'ticks', not 'ns' for debug purposes
// Return values: 0 - success
//                1 - timeout error
int get_rx_word(rx_msg_info_t* msg_info,uint32_t timeout_ns){
  while(rx_word_empty()){
    if(timeout_ns-- == 0)
      return TIMEOUT_ERROR;
  }
  msg_info -> word    = RCV_DATA_WORD_GET();
  msg_info -> status  = RCV_DATA_STATUS_GET();
  msg_info -> errors  = RCV_DATA_ERRORS_GET();
  RCV_IRQ_VECTOR_SET(0);
  return SUCCESS;
}

int min_inter_msg_gap_timeout(){
  return 0;
}

int min_response_gap_timeout(){
  return 0;
}

int max_response_gap_timeout(){
  return 0;
}

void response_gap(int us){
  while(us--){
    // NOP
  }
}

uint32_t get_timestamp_counter(){
  return 0x01234567;
}

void receive_fsm(){

  uint32_t timestamp = get_timestamp_counter();

  uint16_t* subaddr_table_addr = (uint16_t*)(RT_MSG_PTR_TABLE_ADDR_GET()<<1)+RCV_BASE_INDX+(rx_msg_info.word & SUB_ADDR_MASK);

  if(*subaddr_table_addr == 0x0)
    return;

  uint16_t* pointer_table_addr  = (uint16_t*)(*subaddr_table_addr << 1);

  uint16_t data_table_size = (*pointer_table_addr & RX_MSG_TABLE_SIZE_MASK) >> RX_MSG_TABLE_SIZE_OFST;

  if(data_table_size == 0x0){
    // TODO: What to do?
    return;
  }

  lock_rcv_pointer_table();

  uint16_t data_table_indx = (*pointer_table_addr & RX_MSG_TABLE_INDX_MASK) >> RX_MSG_TABLE_INDX_OFST;

  data_table_indx++;

  if(data_table_indx > data_table_size){
    data_table_indx = 1;
  }

  uint16_t* data_table_addr = (uint16_t*)(*pointer_table_addr << 1) + data_table_indx;

  *data_table_addr = (*data_table_addr | RX_DATA_TABLE_LOCK);

  int broadcast = BROADCAST_MSG(rx_msg_info.word);
  int words_cnt = (rx_msg_info.word & WORD_COUNT_MASK);

  if(words_cnt == 0)
    words_cnt = 32;

  *(data_table_addr+1) = ((timestamp >> 16) & 0xFFFF);
  *(data_table_addr+2) = ((timestamp >>  0) & 0xFFFF);

  for(int i = 0; i < words_cnt;;){

    get_rx_word(&rx_msg_info,4);

    if(rx_msg_info.errors){
      // Reset transaction
      return;
    }

    if(rx_msg_info.status == DATA_WORD)
      *(cmd_msg_table_addr + 3 + i) = data;
      i++;
    else
      // TODO: Check if RT-RT no sending to itself
      if(rx_msg_info.word & DIR_MASK)
        if(i == 0)
          continue;
        else
          // Reset transaction
          return;
  }

  if(broadcast){
    *(cmd_msg_table_addr
    update_rcv_msg_table();
    return;
  }

  response_gap(12);

  send_tx_word(0,STATUS_WORD);

  while(tx_word_empty() == 0){
    // NOP
  }

  update_rcv_msg_table();

}

void lock_rcv_pointer_table(){
  *pointer_table_addr = (*pointer_table_addr | RX_MSG_TABLE_LOCK);
}

void unlock_rcv_pointer_table(){
  *pointer_table_addr = (*pointer_table_addr & ~(RX_MSG_TABLE_LOCK));
}

void update_rcv_msg_table(){
  // Set 'update' bit and 'words cnt'
  // Reset 'lock' bit
}

void lock_rcv_msg_table(){
  // Set 'lock' bit
}

