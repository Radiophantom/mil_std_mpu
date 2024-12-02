
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "proc.h"
#include "rcv.h"
#include "xmt.h"

#define MODE_CODE_OP  0
#define TRANSMIT_OP   1
#define RECEIVE_OP    2

typedef enum {
  IDLE,
  RECEIVE,
  TRANSMIT,
  MODE_CODE,
  RESPONSE,
  UPDATE_DATA_TABLE
} state_t;

rx_word_t rx_word;
state_t state;

typedef struct {
  uint32_t  timestamp;
  uint16_t  rt_addr;
  uint16_t  dir;
  uint16_t  sub_addr;
  uint16_t  mode_code;
  uint16_t  data_size;
  uint16_t  data [32];
} msg_t;

int main (){

  msg_t msg;

  state = IDLE;
  // Do some config routines
  // Set 'BUSY' to indicate not valid state ???
  // while(BUSY){ do nothing };

  // Enable receiver and transmitter
  RCV_CONTROL_SET(RCV_CONTROL_ENABLE);
  XMT_CONTROL_SET(XMT_CONTROL_ENABLE);

  uint16_t* pointer_table_addr;

  uint16_t* msg_table_addr;
  uint16_t  msg_table_size;

  uint16_t* data_table_addr;
  uint16_t  data_table_size;
  uint16_t  data_table_indx;

  while(1){

    // Add current mode checks
    // Is it still in RT mode?

    switch(state){

      case IDLE:
        if(get_rx_word(&rx_word,10))
          break;
        msg.timestamp = get_timestamp_counter();
        if(rx_word.word_errors){
          break;
        }
        if(rx_word.word_status != COMMAND_WORD)
          break;
        state = PARSE_MSG;
        break;

      case PARSE_MSG:
        msg.rt_addr   = (rx_word.word_data & RT_ADDR_MASK);
        msg.dir       = (rx_word.word_data & DIR_MASK);
        msg.sub_addr  = (rx_word.word_data & SUB_ADDR_MASK);
        msg.mode_code = (rx_word.word_data & MODE_CODE_MASK);
        msg.word_count= (rx_word.word_data & WORD_COUNT_MASK);
        if(msg.word_count == 0)
          msg.word_count = 32;
        state = CHECK_MSG_ADDRESS;
        break;

      case CHECK_MSG_ADDRESS:
        if(match_rt_address(msg.rt_addr))
          state = CHECK_MSG_LEGALITY;
        else if(!match_broadcast_address(msg.rt_addr))
          state = CHECK_MSG_LEGALITY;
        else
          state = IDLE;
        break;

      case CHECK_MSG_LEGALITY:
        pointer_table_addr  = (uint16_t*)(uintptr_t)(RT_MSG_PTR_TABLE_ADDR_GET() << 1);
        pointer_table_addr += ((msg.cmd & SUB_ADDR_MASK)>>SUB_ADDR_OFST);
        if(match_mode_code_subaddr(msg.cmd))
          pointer_table_addr += MODE_BASE_INDX;
        else if(msg.cmd & DIR_MASK)
          pointer_table_addr += XMT_BASE_INDX;
        else
          pointer_table_addr += RCV_BASE_INDX;
        if(*pointer_table_addr == 0x0000)
          state = IDLE;
        else
          state = GET_MSG_TABLE;
        break;

      case GET_MSG_TABLE:
        msg_table_addr = (uint16_t*)(uintptr_t)(*pointer_table_addr << 1);
        msg_table_size = (*msg_table_addr & MSG_TABLE_SIZE) >> MSG_TABLE_SIZE_OFST;
        if(msg_table_size == 0x0000){
          state = IDLE;
        } else {
          *msg_table_addr = (*msg_table_addr | MSG_TABLE_LOCK);
          state = GET_DATA_TABLE_INDEX;
        }
        break;

      case GET_DATA_TABLE_INDEX:
        data_table_indx = (*msg_table_addr & MSG_TABLE_INDEX) >> MSG_TABLE_INDEX_OFST;
        if(data_table_indx < msg_table_size)
          data_table_indx = 1;
        else
          data_table_indx++;
        state = GET_DATA_TABLE;
        break;

      case GET_DATA_TABLE:
        data_table_addr
        data_table_addr = (uint16_t*)(uintptr_t)(*msg_table_addr << 1) + data_table_indx;
        data_table_size = (*data_table_addr & DATA_TABLE_SIZE_MASK) >> DATA_TABLE_SIZE_OFST;
        if(data_table_size == 0){
          state = IDLE;
          break;
        }
        *data_table_addr = (*data_table_addr | DATA_TABLE_LOCK);
        if(match_mode_code_subaddr(msg.cmd))
          state = MODE_CODE;
        else if(msg.cmd & DIR_MASK)
          state = TRANSMIT;
        else
          state = CHECK_RT_RT_RECEIVE;
        break;

      case CHECK_RT_RT_RECEIVE:
        if(get_rx_word(&rx_word,4)){
          state = IDLE;
          break;
        }
        if(rx_word.word_errors){
          state = IDLE;
          break;
        }
        if((rx_word.word_data & DIR_MASK) && (rx_word.word_status == COMMAND_WORD)){
          state = WAIT_RT_RT_RESPONSE;
          break;
        }
        state = RECEIVE_DATA;
        break;

      case WAIT_RT_RT_RESPONSE:
        state = RECEIVE_DATA;
        if(wait_response(20))
          state = IDLE;
        if(get_rx_word(&rx_word,4))
          state = IDLE;
        break;

      case RECEIVE_DATA:
        int words_cnt = (msg.cmd & WORD_COUNT_MASK);
        if(words_cnt == 0)
          words_cnt = 32;
        for(int i = 0; i < words_cnt; i++){
          msg.data[i] = rx_word.word_data;
          if(get_rx_word(&rx_word,4)){
            state = IDLE;
            break;
          }
        }
        if(match_broadcast_address(msg.cmd))
          state = UPDATE_DATA_TABLE;
        else
          state = WAIT_RESPONSE_GAP;
        break;

      case MODE_CODE:
        state = IDLE;
        switch(rx_word -> word_data & MODE_CODE_MASK){

          case CMD_DYNAMIC_BUS_CONTROL:
            if(broadcast)
              break;
            do_cmd_dynamic_bus_control();
            send_tx_word(0,BASIC_STATUS_GET());
            break;

          case CMD_SYNCHRONIZE:
            do_cmd_synchronize();
            if(broadcast)
              break;
            send_tx_word(0,BASIC_STATUS_GET());
            break;

          case CMD_TRANSMIT_STATUS_WORD:
            if(broadcast)
              break;
            do_cmd_transmit_status_word();
            send_tx_word(0,BASIC_STATUS_GET());
            break;

          case CMD_INITIATE_SELF_TEST:
            do_cmd_initiate_self_test();
            if(broadcast)
              break;
            send_tx_word(0,BASIC_STATUS_GET());
            break;

          case CMD_TRANSMITTER_SHUTDOWN:
            do_cmd_transmitter_shutdown();
            if(broadcast)
              break;
            send_tx_word(0,BASIC_STATUS_GET());
            break;

          case CMD_OVERRIDE_TRANSMITTER_SHUTDOWN:
            do_cmd_override_transmitter_shutdown();
            if(broadcast)
              break;
            send_tx_word(0,BASIC_STATUS_GET());
            break;

          case CMD_INHIBIT_TERMINAL_FLAG_BIT:
            do_cmd_inhibit_terminal_flag_bit();
            if(broadcast)
              break;
            send_tx_word(0,BASIC_STATUS_GET());
            break;

          case CMD_OVERRIDE_INHIBIT_TERMINAL_FLAG_BIT:
            do_cmd_override_inhibit_terminal_flag_bit();
            if(broadcast)
              break;
            send_tx_word(0,BASIC_STATUS_GET());
            break;

          case CMD_RESET_REMOTE_TERMINAL:
            do_cmd_reset_remote_terminal();
            if(broadcast)
              break;
            send_tx_word(0,BASIC_STATUS_GET());
            break;

          case CMD_TRANSMIT_VECTOR_WORD:
            if(broadcast)
              break;
            response_gap(12);
            send_tx_word(0,BASIC_STATUS_GET());
            send_tx_word(1,0xFFFF);
            break;

          case CMD_SYNCHRONIZE_WITH_DATA_WORD:
            if(get_rx_word(&rx_word,4))
              break;
            do_cmd_synchronize_with_data_word();
            break;

          case CMD_TRANSMIT_LAST_COMMAND_WORD:
            if(broadcast)
              break;
            response_gap(12);
            send_tx_word(0,BASIC_STATUS_GET());
            send_tx_word(1,0xFFFF);
            break;

          case CMD_TRANSMIT_BUILT_IN_TEST_WORD:
            if(broadcast)
              break;
            response_gap(12);
            send_tx_word(0,BASIC_STATUS_GET());
            send_tx_word(1,0xFFFF);
            break;

          case CMD_SELECTED_TRANSMITTER:
            if(get_rx_word(&rx_word,4))
              break;
            do_cmd_selected_transmitter();
            break;

          case CMD_OVERRIDE_SELECTED_TRANSMITTER:
            if(get_rx_word(&rx_word,4))
              break;
            do_cmd_override_selected_transmitter();
            break;
        }

      case WAIT_RESPONSE_GAP:
        response_gap(12);
        state = SEND_RESPONSE;
        break;

      case SEND_RESPONSE:
        send_tx_word(1,BASIC_STATUS_GET());
        if(msg.cmd & DIR_MASK)
          state = TRANSMIT;
        else
          state = UPDATE_DATA_TABLE;
        break;

      case TRANSMIT:
        for(int i = 0; i < msg.data_size; i++){
          send_tx_word(0,*(data_table_addr+3+i));
        }
        state = UPDATE_DATA_TABLE;
        break;

      case UPDATE_DATA_TABLE:
        uint16_t data_table_word = *data_table_addr;
        for(int i = 0; i < words_cnt; i++)
          *(data_table_addr+3+i) = msg.data[i];
        // Clear positions
        data_table_word &= ~(DATA_TABLE_UPDATE | DATA_TABLE_BCST | DATA_TABLE_WCNT | DATA_TABLE_LOCK);
        data_table_word |= (msg.cmd & DATA_TABLE_WCNT);
        data_table_word |= match_broadcast_address(msg.cmd) ? DATA_TABLE_BCST : 0;
        data_table_word |= (msg.cmd & DIR_MASK) ? 0 : DATA_TABLE_UPDATE;
        *data_table_addr = data_table_word;
        state = UPDATE_MSG_TABLE;
        break;

      case UPDATE_MSG_TABLE:
        uint16_t msg_table_word = *msg_table_addr;
        msg_table_word &= ~((MSG_TABLE_INDEX << MSG_TABLE_INDEX_OFST) | (MSG_TABLE_LOCK));
        msg_table_word |= (data_table_indx << MSG_TABLE_INDEX_OFST);
        *msg_table_addr = msg_table_word;
        state = IDLE;
        break;

      default:
        break;
    }
  }
  return 0;
}

int match_rt_address(uint16_t rt_address){
  return (rt_address == (BASIC_STATUS_GET() & RT_ADDR_MASK));
}

int match_broadcast_address(uint16_t word_data){
  return ((word_data & RT_ADDR_MASK) == BROADCAST_ADDR);
}

int match_mode_code_subaddr(uint16_t word_data){
  if((word_data & SUB_ADDR_MASK) == MODE_CODE_ADDR0)
    return 1;
  if((word_data & SUB_ADDR_MASK) == MODE_CODE_ADDR1)
    return 1;
  return 0;
}

int check_minimum_response_time(){
  // NOP
}

