
#include "xmt.h"

void ERROR() {
}

short tx_buf [32];

State transmit_fsm () {

  switch(current_state){

    TRANSMIT_S:
      tx_buf_ptr = 0;
      return SEND_RESPONSE_S;

    TRANSMIT_DATA_S:
      tx_msg_info.msg_type  = 0x1;
      tx_msg_info.data      = tx_buf[tx_buf_ptr++];
      send_tx_word(&tx_msg_info);
      if(rx_msg_info.words == tx_buf_ptr)
        // DO STUFF
        return IDLE_S;
      return TRANSMIT_DATA_S;
  }
}

void do_transmit(){

  unsigned short* rt_msg_table_addr;
  unsigned short* cmd_msg_table_addr;

  rt_msg_table_addr  = (unsigned short*)RT_MSG_PTR_TABLE_ADDR_GET();
  cmd_msg_table_addr = rt_msg_table_addr+64+(rx_msg_info.word & SUB_ADDR_MASK);

}

