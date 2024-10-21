
#include "ctrl_regs.h"
#include "mil_std.h"

void set_watchdog_us(int us){
  // USE BSP to launch watchdog
}

volatile unsigned char BROADCAST_FLAG;
volatile unsigned char OP_DIR; // 0 - RECEIVE, 1 - TRANSMIT

volatile unsigned short STATUS_WORD = 0x0000;

volatile unsigned short RESPONSE_SUPPRES = 0;

volatile unsigned char usercast;
volatile unsigned char broadcast;
volatile unsigned char mode_code;

void transmit_fsm () {

  TRANSMIT_S:
    // DO STUFF
    set_status_reg(0x0);
    WAIT_S;

  TRANSMIT_DATA_S:
    if(words_cnt == msg.words_cnt)
      IDLE_S;
}

void mode_code_fsm () {

  int mode_code_op = mode_code_valid(mcode);

  if(mode_code_op == -1)
    // DO STUFF
    SKIP_S;

  MODE_CODE_S:
    if(mode_code_op & EXTRA_DATA)
      // DO STUFF
      if(mode_code_op & BROADCAST)
        IDLE_S;
      else
        WAIT_S;
    else
      if(cmd == TRANSMIT)
        WAIT_S;
      else
        RECEIVE_MODE_CODE_DATA_S;

  TRANSMIT_MODE_CODE_DATA_S:
    IDLE_S;

  RECEIVE_MODE_CODE_DATA_S:
    if(cmd != DATA)
      // ERROR
    else
      // DO STUFF
      if(broadcast)
        IDLE_S;
      else
        WAIT_S;
}

void receive_fsm () {

  RECEIVE_S:
    RECEIVE_FIRST_WORD_S;
  
  RECEIVE_FIRST_WORD_S:
    if(cmd == RECEIVE)
      // ERROR
    else if(cmd == TRANSMIT)
      RT_RT_OP_S;
    else
      RECEIVE_DATA_S;

  RECEIVE_DATA_S:
    if(cmd != DATA)
      // ERROR
    else
      if(words_cnt == msg.words_cnt)
        // DO STUFF
        if(broadcast)
          IDLE_S;
        else
          WAIT_S;

}

void main_fsm () {

  IDLE_S:
    if(msg_received){
      if(msg_invalid)
        // DO STUFF
        SKIP_S;
      else
        if(cmd == DATA)
          // DO STUFF
          SKIP_S;
        if(check_addr() == OK)
          if(mode_code == true)
            mode_code_fsm();
          else if(cmd == RECEIVE)
            receive_fsm();
          else
            transmit_fsm();
    }

  WAIT_S:
    if(gap_cnt == response_cnt)
      SEND_RESPONSE;

  SEND_RESPONSE:
    if(cmd == TRANSMIT)
      TRANSMIT_DATA_S;
    else if(cmd == RECEIVE_S)
      IDLE_S;
    else if(cmd == MODE_CODE_S)
      IDLE_S;
    WAIT_S:
      if(gap_cnt == IFG)
        SEND_RESPONSE;

}

volatile rx_msg_info_t rx_msg_info;
volatile tx_msg_info_t tx_msg_info;

volatile rx_msg_flag;
volatile tx_msg_flag;

void msg_processor_unit() {

  while(1){

    if!(rx_msg_flag || tx_msg_flag){
      nop;

    if(rx_msg_flag || tx_msg_flag){

    next_fsm_state = get_next_fsm_state();

    if(rx_msg_info.rt_address == 31){
      BROADCAST_FLAG = 1;
    } else if(rx_msg_info.rt_address == BASIC_STATUS_RT_ADDR_GET(basic_status) ){
      BROADCAST_FLAG = 0;
    } else {
      // SKIP in all other cases
      continue;
    }

    unsigned short* rt_msg_table_addr  = RT_MSG_PTR_TABLE_ADDR_GET(BASE_ADDR);
    unsigned short* cmd_msg_table_addr;

    if((rx_msg_info.sub_address == 0 ) || \
       (rx_msg_info.sub_address == 31)){
      cmd_msg_table_addr = rt_msg_table_addr+64+rx_msg_info.sub_address*2;
    } else if(rx_msg_info.cmd == 0){
      cmd_msg_table_addr = rt_msg_table_addr+0+rx_msg_info.sub_address*2;
    } else {
      cmd_msg_table_addr = rt_msg_table_addr+32+rx_msg_info.sub_address*2;
    }

    if(rx_msg_info.cmd == 0){

      OP_DIR = 0;

      for(int i = 0; i < rx_msg_info.words_cnt; i++ ){
        wait_rx_word(BASE_ADDR);
        get_rx_word(BASE_ADDR,&rx_msg_info);
        // 
      }

      tx_msg_info.msg_type  = 0x0;
      tx_msg_info.data      = STATUS_WORD;

      send_tx_word(BASE_ADDR,&tx_msg_info);
      wait_tx_word(BASE_ADDR);

    } else {

      OP_DIR = 1;

      tx_msg_info.msg_type  = 0x0;
      tx_msg_info.data      = STATUS_WORD;

      send_tx_word(BASE_ADDR,&tx_msg_info);
      wait_tx_word(BASE_ADDR);

      for(int i = 0; i < main_msg_info.words_cnt; i++){
        //
        tx_msg_info.msg_type  = 0x1;
        tx_msg_info.data      = tx_data--;
        send_tx_word(BASE_ADDR,&tx_msg_info);
      }
    }
  }

}

