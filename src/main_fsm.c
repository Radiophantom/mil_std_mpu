
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
  FINISH
} state_t;

rx_word_t rx_word;
state_t state;

typedef struct {
  uint8_t op_type;
  uint8_t words_cnt;
  uint8_t broadcast;
} msg_t;

int main (){

  msg_t msg_info;
  uint16_t rx_buf [32];
  uint8_t  rx_ptr;
  uint8_t  tx_ptr;

  state = IDLE;
  // Do some config routines
  // Set 'BUSY' to indicate not valid state ???
  // while(BUSY){ do nothing };

  // Enable receiver and transmitter
  RCV_CONTROL_SET(RCV_CONTROL_ENABLE);
  XMT_CONTROL_SET(XMT_CONTROL_ENABLE);

  uint32_t  msg_timestamp;
  uint16_t* pointer_table_addr;
  uint16_t* msg_table_addr;
  uint16_t* data_table_addr;

  uint16_t data_table_size;
  uint16_t data_table_indx;

  while(1){

    switch(state){

      case IDLE:
        if(get_rx_word(&rx_word,10))
          break;
        msg_timestamp = get_timestamp_counter();
        if(rx_word.word_errors){
          break;
        }
        if(rx_word.word_status != COMMAND_WORD)
          break;
        if(!check_rt_address(&rx_word) && !check_broadcast_address(&rx_word)){
          break;
        }
        state = CHECK_MSG_LEGALITY;
        rx_ptr = 0;
        tx_ptr = 0;
        break;

      case CHECK_MSG_LEGALITY:
        if(check_mode_code(&rx_word)){
          //msg_info.op_type = MODE_CODE_OP;
          pointer_table_addr = (uint16_t*)(uintptr_t)(RT_MSG_PTR_TABLE_ADDR_GET() << 1)+MODE_BASE_INDX+((rx_word -> word_data & SUB_ADDR_MASK)>>SUB_ADDR_OFST);
        }
        else if(rx_word.word_data & DIR_MASK){
          //msg_info.op_type = TRANSMIT_OP;
          pointer_table_addr = (uint16_t*)(uintptr_t)(RT_MSG_PTR_TABLE_ADDR_GET() << 1)+XMT_BASE_INDX+((rx_word -> word_data & SUB_ADDR_MASK)>>SUB_ADDR_OFST);
        } else {
          //msg_info.op_type = RECEIVE_OP;
          pointer_table_addr = (uint16_t*)(uintptr_t)(RT_MSG_PTR_TABLE_ADDR_GET() << 1)+RCV_BASE_INDX+((rx_word -> word_data & SUB_ADDR_MASK)>>SUB_ADDR_OFST);
        }

        if(*pointer_table_addr == 0x0000){
          state = IDLE;
          break;
        }
        state = GET_MSG_TABLE;
        break;

      case GET_MSG_TABLE:
        msg_table_addr = (uint16_t*)(uintptr_t)(*pointer_table_addr << 1);
        msg_table_size = (*msg_table_addr & MSG_TABLE_SIZE_MASK) >> MSG_TABLE_SIZE_OFST;

        if(msg_table_size == 0){
          state = IDLE;
          break;
        }
        data_table_indx = (*msg_table_addr & MSG_TABLE_INDEX_MASK) >> MSG_TABLE_INDEX_OFST;
        data_table_indx++;
        if(data_table_indx > msg_table_size)
          data_table_indx = 1;
        state = GET_DATA_TABLE;
        msg_table_lock(msg_table_addr);
        break;

      case GET_DATA_TABLE:
        data_table_addr = (uint16_t*)(uintptr_t)(*msg_table_addr << 1) + data_table_indx;
        data_table_size = (*data_table_addr & DATA_TABLE_SIZE_MASK) >> DATA_TABLE_SIZE_OFST;

        if(data_table_size == 0){
          state = IDLE;
          break;
        }
        state = PARSE_MSG;
        data_table_lock(data_table_addr);
        break;

      case PARSE_MSG:

        msg_info.broadcast = check_broadcast_address(&rx_word);
        msg_info.words_cnt = (rx_word -> word_data & WORD_COUNT_MASK);
        msg_info.mode_code = (rx_word -> word_data & MODE_CODE_MASK);

        if(msg_info.words_cnt == 0)
          msg_info.words_cnt = 32;

        if(check_mode_code(&rx_word)){
          msg_info.op_type = MODE_CODE_OP;
          state = MODE_CODE;
        }
        else if(rx_word.word_data & DIR_MASK){
          msg_info.op_type = TRANSMIT_OP;
          state = RESPONSE;
        } else {
          msg_info.op_type = RECEIVE_OP;
          state = RECEIVE;
        }
        break;

      case RECEIVE:
        if(get_rx_word(&rx_word,4)){
          state = IDLE;
          break;
        }
        if(rx_word.word_errors){
          state = IDLE;
          break;
        }
        //if((rx_word.word_data & DIR_MASK) && (rx_word.word_status == COMMAND_WORD)){
        //  state = RT_RT_TRANSFER;
        //  break;
        //}
        rx_buf[rx_ptr++] = rx_word.word_data;
        if(rx_ptr == msg_info.words_cnt)
          if(msg_info.broadcast)
            state = FINISH;
          else
            state = RESPONSE;
        break;

      case MODE_CODE:
        switch(rx_word -> word_data & MODE_CODE_MASK){

          case CMD_DYNAMIC_BUS_CONTROL:
            if(broadcast){
              // Reset transaction
              return;
            }
            do_cmd_dynamic_bus_control();
            send_tx_word(0,BASIC_STATUS_GET());
            break;

        }

      case RESPONSE:
        response_gap(12);
        send_tx_word(0,BASIC_STATUS_GET());
        if(msg_info.op_type == TRANSMIT_OP)
          state = TRANSMIT;
        else
          if(msg_info.op_type == MODE_CODE_OP && response_enable)
            state = MODE_CODE;
          else
            state = FINISH;
        break;

      case TRANSMIT:
        send_tx_word(1,*(data_table_addr+3+tx_ptr++));
        if(tx_ptr == words_cnt){
          state = FINISH;
          break;
        }

      case FINISH:
        if(msg_info.op_type == RECEIVE_OP)
          for(int i = 0; i < words_cnt; i++)
            *(data_table_addr+3+i) = rx_buf[i];
        if(msg_info.op_type == RECEIVE_OP)
          if(msg_info.broadcast)
            *data_table_addr = *data_table_addr | DATA_TABLE_BCST | DATA_TABLE_UPDATE | (msg_info.words_cnt & DATA_TABLE_WCNT);
          else
            *data_table_addr = *data_table_addr | DATA_TABLE_UPDATE | (msg_info.words_cnt & DATA_TABLE_WCNT);
        else
          *data_table_addr = *data_table_addr & ~(DATA_TABLE_UPDATE);
          *data_table_addr = *data_table_addr | DATA_TABLE_UPDATE | (msg_info.words_cnt & DATA_TABLE_WCNT);
        *msg_table_addr  = *msg_table_addr  | data_table_indx;
        data_table_unlock(data_table_addr);
        msg_table_unlock(msg_table_addr);
        state = IDLE;
        break;
    }
  }
  return 0;
}

int check_rt_address(rx_word_t* rx_word){
  return ((rx_word -> word_data & RT_ADDR_MASK) == (BASIC_STATUS_GET() & RT_ADDR_MASK));
}

int check_broadcast_address(rx_word_t* rx_word){
  return ((rx_word -> word_data & RT_ADDR_MASK) == BROADCAST_ADDR);
}


int check_mode_code(rx_word_t* rx_word){
  if((rx_word -> word_data & SUB_ADDR_MASK) == MODE_CODE_ADDR0)
    return 1;
  if((rx_word -> word_data & SUB_ADDR_MASK) == MODE_CODE_ADDR1)
    return 1;
  return 0;
}
