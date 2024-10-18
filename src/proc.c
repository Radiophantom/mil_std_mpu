
#include "ctrl_regs.h"
#include "mil_std.h"

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
    WAIT_S;

  TRANSMIT_DATA_S:
    if(words_cnt == msg.words_cnt)
      IDLE_S;
}

int mode_code_valid() {
  if((mode_code <= 8) && (cmd == 1))
    return 1;
  if((mode_code == 16 && cmd == ) || (mode_code 
}

int mode_code_no_data() {
  if(mode_code <= 47)
    return 1;
  return 0;
}

int mode_code_reserved () {
  if((mode_code > 40) && (mode_code < 48))
    return 1;
  if((
    return 
void mode_code_fsm () {

  MODE_CODE_S:
    if(mode_code_no_data)
      // DO STUFF
      if(broadcast)
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


void rt_msg_processor(unsigned short* BASE_ADDR) {

  rx_msg_info_t rx_msg_info;
  tx_msg_info_t tx_msg_info;

  while(1){

    wait_rx_word();
    get_rx_word(&rx_msg_info);

    unsigned short basic_status = BASIC_STATUS_GET();

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

////typedef struct {
////  unsigned char   rt_address;
////  unsigned char   msg_error;
////  //unsigned char   instr_bit;
////  //unsigned char   service_req;
////  unsigned char   bcst_rcvd;
////  //unsigned char   busy;
////  //unsigned char   subsys_flag;
////  //unsigned char   dyn_bus_accept;
////  //unsigned char   terminal_flag;
////} stat_data_t;
////
////typedef struct {
////  unsigned char   msg_type; // 0 - COMMAND, 1 - DATA
////  unsigned short  msg_data;
////} tx_msg_info_t;
//
//void rt_msg_processor(){
//
//  rx_msg_info_t rx_msg_info;
//  tx_msg_info_t tx_msg_info;
//
//  while(1){
//
//    receive_word(rx_msg_info);
//
//    if(rx_msg_info.cmd == 0){
//      // Receive command
//      if(rx_msg_info.mode_code){
//        // Mode code command
//        if(rx_msg_info.mode_code_wdata){
//          receive_word();
//        }
//      } else {
//        // Receive data command
//        receive_word();
//        if(rx_msg_info.cmd == 1){
//          // RT - RT transaction
//          receive_word();
//        }
//        unsigned char word_cnt = (rx_msg_info.word_cnt == 0) ? 32 : rx_msg_info.word_cnt;
//        while(word_cnt){
//          receive_word();
//          word_cnt--;
//        }
//      }
//      if(rx_msg_info.broadcast){
//        // SKIP status word
//      } else {
//        wait_gap();
//        send_status_word();
//      }
//    } else {
//      // Transmit command
//      wait_gap();
//      send_status_word();
//      if(rx_msg_info.mode_code){
//        transmit_word();
//      } else {
//        unsigned char word_cnt = (rx_msg_info.word_cnt == 0) ? 32 : rx_msg_info.word_cnt;
//        while(word_cnt){
//          transmit_word();
//          word_cnt--;
//        }
//      }
//    }
//}
//
