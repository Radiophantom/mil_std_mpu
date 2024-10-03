
#ifndef __RECEIVE_PROC_H__
#define __RECEIVE_PROC_H__

#include "ctrl_regs.h"

#define COMMAND_WORD  0
#define DATA_WORD     1

#define RECEIVE_MSG   0
#define TRANSMIT_MSG  1

typedef struct {
  unsigned short  sync;
  unsigned short  data;
  unsigned short  timestampl;
  unsigned short  timestamph;
  unsigned short  errors;
} rx_msg_regs_t;

typedef struct {
  unsigned char   msg_type;
  unsigned char   rt_address;
  unsigned char   cmd;
  unsigned char   sub_address;
  unsigned char   word_count;
  unsigned char   broadcast;
  unsigned char   unicast;
  unsigned char   mode_code;
  unsigned short  data;
  unsigned int    timestamp;
  unsigned char   errors;
} cmd_word_t;

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
void msg_processor(){

  rx_msg_info_t rx_msg_info;
  tx_msg_info_t tx_msg_info;

  while(1){

    receive_word(&rx_msg_info);

    if(rx_msg_info.cmd == RECEIVE_MSG){
      // Receive command
      if(msg_info.mode_code){
        // Mode code command
        if(msg_info.word_count >> 4){
          receive_word(&rx_msg_info);
        }
      } else {
        // Receive data command
        receive_word(&rx_msg_info);
        if(msg_info.cmd == TRANSMIT_MSG){
          // RT - RT transaction
          receive_word(&rx_msg_info);
        }
        unsigned char word_cnt = (msg_info.word_cnt == 0) ? 32 : msg_info.word_cnt;
        while(word_cnt){
          receive_word(&rx_msg_info);
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

void wait_rx_msg(){
  while(RX_VALID == 0){
  }
}

void receive_word(rx_msg_info_t* msg_info){

  rx_msg_regs_t rx_msg_regs;
  cmd_word_t    cmd_word;

  // Polling 'RCV_VALID' bit
  wait_rx_msg();

  // Read 'RCV_MSG' registers
  rx_msg_regs.sync        = *(RD_SYNC);
  rx_msg_regs.data        = *(RD_DATA);
  rx_msg_regs.timestampl  = *(RD_TIMESTAMPL);
  rx_msg_regs.timestamph  = *(RD_TIMESTAMPH);
  rx_msg_regs.errors      = *(RD_ERROR);

  // Parse received message
  cmd_word.msg_type     = rx_msg_regs.sync;
  cmd_word.rt_address   = _GET_BITS(rx_msg_regs.data,0x1F,11);
  cmd_word.cmd          = _GET_BITS(rx_msg_regs.data,0x1,10);
  cmd_word.sub_address  = _GET_BITS(rx_msg_regs.data,0x1F,5);
  cmd_word.word_count   = _GET_BITS(rx_msg_regs.data,0x1F,0);
  cmd_word.broadcast    = (cmd_word.rt_address == 31);
  cmd_word.unicast      = (cmd_word.rt_address == *(RD_RT_ADDR)); // TODO: Check not to config 31 addr to be unicast!
  cmd_word.mode_code    = (cmd_word.sub_addr == 0) || (cmd_word.sub_addr == 31);
  cmd_word.data         = rx_msg_regs.data;
  cmd_word.timestamp    = (rx_msg_regs.timestamph << 16) | rx_msg_regs.timestampl;
  cmd_word.errors       = rx_msg_regs.errors;
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

