
#include "mode_code.h"

void mode_code_fsm(){

  uint16_t* pointer_table_addr;
  uint16_t* msg_table_addr;
  uint16_t* data_table_addr;

  uint32_t timestamp;
  uint16_t data_table_size;
  uint16_t data_table_indx;

  int      broadcast;
  uint8_t  words_cnt;

  timestamp = get_timestamp_counter();

  if((rx_word.word_data & RT_ADDR_MASK) != BROADCAST_ADDR)
    // Ignore message and suppress response
    //return;
  else if((rx_word.word_data & RT_ADDR_MASK) != (BASIC_STATUS_GET() & RT_ADDR_MASK))
    // Ignore message and suppress response
    return;

  pointer_table_addr = (uint16_t*)(RT_MSG_PTR_TABLE_ADDR_GET()<<1)+MODE_CODE_BASE_INDX+((rx_word.word_data & SUB_ADDR_MASK)>>SUB_ADDR_OFST);
  if(*pointer_table_addr == 0x0)
    // Ignore message and suppress response
    return;

  msg_table_addr = (uint16_t*)(*pointer_table_addr << 1);

  msg_table_lock(msg_table_addr);

  data_table_size = (*msg_table_addr & MSG_TABLE_SIZE_MASK) >> MSG_TABLE_SIZE_OFST;
  if(data_table_size == 0x0){
    // TODO: Means virgin data set. So always should be minimum 1 data table if pointer is ON ???
    data_table_indx = 0;
  } else {
    data_table_indx = (*msg_table_addr & MSG_TABLE_INDX_MASK) >> MSG_TABLE_INDX_OFST;
  }

  data_table_indx++;
  if(data_table_indx > data_table_size){
    data_table_indx = 1;
  }

  data_table_addr = (uint16_t*)(*msg_table_addr << 1) + data_table_indx;

  data_table_lock(data_table_addr);

  broadcast = ((rx_word.word_data & RT_ADDR_MASK) == BROADCAST_ADDR);
  words_cnt = (rx_word.word_data & WORD_COUNT_MASK);

  if(words_cnt == 0)
    words_cnt = 32;

  switch(rx_msg_info.word & MODE_CODE_MASK){

    case CMD_DYNAMIC_BUS_CONTROL:
      if(broadcast){
        // Reset transaction
        return;
      }
      do_cmd_dynamic_bus_control();
      send_tx_word(0,STATUS_WORD);
      break;

    case CMD_SYNCHRONIZE:
      do_cmd_synchronize();
      if(broadcast)
        return;
      send_tx_word(0,STATUS_WORD);
      break;

    case CMD_TRANSMIT_STATUS_WORD:
      if(broadcast){
        // Reset transaction
        return;
      }
      do_cmd_transmit_status_word();
      send_tx_word(0,STATUS_WORD);
      break;

    case CMD_INITIATE_SELF_TEST:
      do_cmd_initiate_self_test();
      if(broadcast)
        return;
      send_tx_word(0,STATUS_WORD);
      break;

    case CMD_TRANSMITTER_SHUTDOWN:
      do_cmd_transmitter_shutdown();
      if(broadcast)
        return;
      send_tx_word(0,STATUS_WORD);
      break;

    case CMD_OVERRIDE_TRANSMITTER_SHUTDOWN:
      do_cmd_override_transmitter_shutdown();
      if(broadcast)
        return;
      send_tx_word(0,STATUS_WORD);
      break;

    case CMD_INHIBIT_TERMINAL_FLAG_BIT:
      do_cmd_inhibit_terminal_flag_bit();
      if(broadcast)
        return;
      send_tx_word(0,STATUS_WORD);
      break;

    case CMD_OVERRIDE_INHIBIT_TERMINAL_FLAG_BIT:
      do_cmd_override_inhibit_terminal_flag_bit();
      if(broadcast)
        return;
      send_tx_word(0,STATUS_WORD);
      break;

    case CMD_RESET_REMOTE_TERMINAL:
      do_cmd_reset_remote_terminal();
      if(broadcast)
        return;
      send_tx_word(0,STATUS_WORD);
      break;

    case CMD_TRANSMIT_VECTOR_WORD:
      if(broadcast)
        // Reset transaction
        return;
      response_gap(12);
      send_tx_word(0,STATUS_WORD);
      send_tx_word(1,0xXXXX);
      break;

    case CMD_SYNCHRONIZE_WITH_DATA_WORD:
      while(rx_word_empty()){
        if(min_inter_msg_gap_timeout() || max_inter_msg_gap_timeout())
          // Reset transaction
          return;
      }
      get_rx_word(rx_msg_info);
      do_cmd_synchronize_with_data_word();
      break;

    case CMD_TRANSMIT_LAST_COMMAND_WORD:
      if(broadcast)
        // Reset transaction
        return;
      response_gap(12);
      send_tx_word(0,STATUS_WORD);
      send_tx_word(1,0xXXXX);
      break;

    case CMD_TRANSMIT_BUILT_IN_TEST_WORD:
      if(broadcast)
        // Reset transaction
        return;
      response_gap(12);
      send_tx_word(0,STATUS_WORD);
      send_tx_word(1,0xXXXX);
      break;

    case CMD_SELECTED_TRANSMITTER:
      while(rx_word_empty()){
        if(min_inter_msg_gap_timeout() || max_inter_msg_gap_timeout())
          // Reset transaction
          return;
      }
      get_rx_word(rx_msg_info);
      do_cmd_selected_transmitter();
      break;

    case CMD_OVERRIDE_SELECTED_TRANSMITTER:
      while(rx_word_empty()){
        if(min_inter_msg_gap_timeout() || max_inter_msg_gap_timeout())
          // Reset transaction
          return;
      }
      get_rx_word(rx_msg_info);
      do_cmd_override_selected_transmitter();
      break;

    default:
      return;
  }
}

