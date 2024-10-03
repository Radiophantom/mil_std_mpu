
#ifndef __PROC_H__
#define __PROC_H__

#include "ctrl_regs.h"

#define COMMAND_WORD  0
#define DATA_WORD     1

#define RECEIVE_MSG   0
#define TRANSMIT_MSG  1

typedef struct {
  unsigned char   msg_type;
  unsigned short  msg_data;
  unsigned int    msg_timestamp;
  unsigned char   msg_errors; // 0 bit - parity error
} rx_msg_t;

typedef struct {
  unsigned char   rt_address;
  unsigned char   cmd; // 0 - RECEIVE, 1 - TRANSMIT
  unsigned char   sub_address;
  unsigned char   words_cnt;
} cmd_data_t;

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
} tx_msg_t;

void receive_msg_hander(){
  if(rx_msg.msg_type == COMMAND_WORD)}
    command_word_handler(rx_msg);
  } else {
    data_word_handler(rx_msg);
  }
}

// (rt_address == 0-30)  - Unique addr
// (rt_address == 31)    - Broadcast addr
// (sub_addr  == 0 or 31)- mode code
msg_info_t parse_msg(rx_msg_t* rx_msg){

  msg_info_t msg_info;

  msg_info.msg_type     = rx_msg -> msg_type;
  msg_info.rt_address   = _GET_BITS(rx_msg.msg_data,0x1F,11);
  msg_info.cmd          = _GET_BITS(rx_msg.msg_data,0x1,10);
  msg_info.sub_address  = _GET_BITS(rx_msg.msg_data,0x1F,5);
  msg_info.word_count   = _GET_BITS(rx_msg.msg_data,0x1F,0);

  msg_info.broadcast    = (msg_info.rt_address == 31);
  msg_info.unicast      = (msg_info.rt_address == RT_ADDR); // TODO: Check not to config 31 addr to be unicast!
  msg_info.mode_code    = (msg_info.sub_addr == 0) || (msg_info.sub_addr == 31);

  return msg_info;
}

// (mode_code 00000 -> 01111) - with NO data word
// (mode_code 10000 -> 11111) - with 1 data word
// (word_cnt == 1 - 31) - 1-31 words
// (word_cnt == 0)      - 32 words
void msg_processor(msg_info_t msg_info){

  if(msg_info.cmd == RECEIVE_MSG){
    // Receive command
    if(msg_info.mode_code){
      // Mode code command
      if(msg_info.word_count >> 4){
        receive_data_word();
      }
    } else {
      // Receive data command
      receive_data_word();
      if(msg_info.cmd == TRANSMIT_MSG){
        // RT - RT transaction
        receive_data_word();
      }
      unsigned char word_cnt = (msg_info.word_cnt == 0) ? 32 : msg_info.word_cnt;
      while(word_cnt){
        receive_data_word();
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
      transmit_data();
    } else {
      unsigned char word_cnt = (msg_info.word_cnt == 0) ? 32 : msg_info.word_cnt;
      while(word_cnt){
        transmit_data();
        word_cnt--;
      }
    }
  }
}

void mode_code_error(msg_info_t* msg_info){
  if(msg_info.mode_code && msg_info.msg_type == TRANSMIT_MSG)
    return 1;
  if(msg_info.mode_code && msg_info.broadcast && 
  // Broadcast address
  if(msg_data.sub_address == 0 || msg_data.sub_address == 31){
    // MODE CODE
    if( (words_cnt == 1 ) ||
        (words_cnt == 3 ) ||
        (words_cnt == 4 ) ||
        (words_cnt == 5 ) ||
        (words_cnt == 6 ) ||
        (words_cnt == 7 ) ||
        (words_cnt == 8 ) ||
        (words_cnt == 17) ||
        (words_cnt == 20) ||
        (words_cnt == 21)   ){
      if( (words_cnt == 17) ||
          (words_cnt == 20) ||
          (words_cnt == 21)   ){

#endif

