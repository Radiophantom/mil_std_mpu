
#include "rcv.h"

int rx_word_available(){
  return RCV_IRQ_VECTOR_RCV_GET(RCV_IRQ_VECTOR_GET());
}

void rx_word_accepted(){
  RCV_IRQ_VECTOR_SET(0);
}

void get_rx_word(rx_msg_info_t* msg_info){
  msg_info -> word    = RCV_DATA_WORD_GET();
  msg_info -> status  = RCV_DATA_STATUS_GET();
  msg_info -> errors  = RCV_DATA_ERRORS_GET();
}

void ERROR(){
}

volatile int broadcast;

// TODO: Change to directly writing to shared MEM
short rx_data_buf [32];
short rx_data_buf_indx;

State receive_fsm () {

  switch(current_state){

    RECEIVE_S:
      broadcast = BROADCAST_MSG(rx_msg_info.word);
      rx_data_buf_indx = 0;
      return RECEIVE_FIRST_WORD_S;
  
    RECEIVE_FIRST_WORD_S:
      if(rx_msg_info.word & DIR_MASK)
        return RT_RT_OP_S;
      else
        *(rx_data_buf+rx_data_buf_indx) = rx_msg_info.word;
        rx_data_buf_indx++;
        if(rx_msg_info.words == rx_data_buf_indx)
          if(broadcast)
            // DO receive operation stuff
            return IDLE_S;
          else
            return SEND_RESPONSE_S;
        else
          return RECEIVE_DATA_S;

    RECEIVE_DATA_S:
      *(rx_data_buf+rx_data_buf_indx) = rx_msg_info.word;
      rx_data_buf_indx++;
      if(rx_msg_info.words == rx_data_buf_indx)
        if(broadcast)
          // DO receive operation stuff
          return IDLE_S;
        else
          return SEND_RESPONSE_S;
      else
        return RECEIVE_DATA_S;

}

void do_receive_data(){

  unsigned short* rt_msg_table_addr;
  unsigned short* cmd_msg_table_addr;

  rt_msg_table_addr  = (unsigned short*)RT_MSG_PTR_TABLE_ADDR_GET();
  cmd_msg_table_addr = rt_msg_table_addr+0+(rx_msg_info.word & SUB_ADDR_MASK);

}

