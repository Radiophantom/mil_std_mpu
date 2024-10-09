
#include "ctrl_regs.h"

#define RECEIVE_MSG   0
#define TRANSMIT_MSG  1

typedef struct {
  unsigned char   rt_address;
  unsigned char   msg_error;
  //unsigned char   instr_bit;
  //unsigned char   service_req;
  unsigned char   bcst_rcvd;
  //unsigned char   busy;
  //unsigned char   subsys_flag;
  //unsigned char   dyn_bus_accept;
  //unsigned char   terminal_flag;
} stat_data_t;

typedef struct {
  unsigned char   msg_type; // 0 - COMMAND, 1 - DATA
  unsigned short  msg_data;
} tx_msg_info_t;

void rt_msg_processor(){

  rx_msg_info_t rx_msg_info;
  tx_msg_info_t tx_msg_info;

  while(1){

    receive_word(rx_msg_info);

    if(msg_info.cmd == RECEIVE_MSG){
      // Receive command
      if(msg_info.mode_code){
        // Mode code command
        if(msg_info.word_count >> 4){
          receive_word();
        }
      } else {
        // Receive data command
        receive_word();
        if(msg_info.cmd == TRANSMIT_MSG){
          // RT - RT transaction
          receive_word();
        }
        unsigned char word_cnt = (msg_info.word_cnt == 0) ? 32 : msg_info.word_cnt;
        while(word_cnt){
          receive_word();
          word_cnt--;
        }
      }
      if(msg_info.broadcast){
        // SKIP status word
      } else {
        wait_gap();
        send_status_word();
      }
    } else {
      // Transmit command
      wait_gap();
      send_status_word();
      if(msg_info.mode_code){
        transmit_word();
      } else {
        unsigned char word_cnt = (msg_info.word_cnt == 0) ? 32 : msg_info.word_cnt;
        while(word_cnt){
          transmit_word();
          word_cnt--;
        }
      }
    }
}

