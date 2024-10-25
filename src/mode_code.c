
#include "mode_code.h"

void mode_code_fsm(){

  int timestamp = get_timestamp_counter();

  lock_mcode_msg_table();

  uint16_t* rt_msg_table_addr     = (uint16_t*)RT_MSG_PTR_TABLE_ADDR_GET();
  uint16_t* mcode_msg_table_addr  = rt_msg_table_addr+32+(rx_msg_info.word & SUB_ADDR_MASK);

  int broadcast = BROADCAST_MSG(rx_msg_info.word);

  switch(rx_msg_info.word & MODE_CODE_MASK){

    case CMD_DYNAMIC_BUS_CONTROL:
      if(broadcast){
        // Reset transaction
        return;
      }
      do_cmd_dynamic_bus_control();
      send_response(STATUS_WORD);
      break;

    case CMD_SYNCHRONIZE:
      do_cmd_synchronize();
      if(broadcast)
        return;
      send_response(STATUS_WORD);
      break;

    case CMD_TRANSMIT_STATUS_WORD:
      if(broadcast){
        // Reset transaction
        return;
      }
      do_cmd_transmit_status_word();
      send_response(STATUS_WORD);
      break;

    case CMD_INITIATE_SELF_TEST:
      do_cmd_initiate_self_test();
      if(broadcast)
        return;
      send_response(STATUS_WORD);
      break;

    case CMD_TRANSMITTER_SHUTDOWN:
      do_cmd_transmitter_shutdown();
      if(broadcast)
        return;
      send_response(STATUS_WORD);
      break;

    case CMD_OVERRIDE_TRANSMITTER_SHUTDOWN:
      do_cmd_override_transmitter_shutdown();
      if(broadcast)
        return;
      send_response(STATUS_WORD);
      break;

    case CMD_INHIBIT_TERMINAL_FLAG_BIT:
      do_cmd_inhibit_terminal_flag_bit();
      if(broadcast)
        return;
      send_response(STATUS_WORD);
      break;

    case CMD_OVERRIDE_INHIBIT_TERMINAL_FLAG_BIT:
      do_cmd_override_inhibit_terminal_flag_bit();
      if(broadcast)
        return;
      send_response(STATUS_WORD);
      break;

    case CMD_RESET_REMOTE_TERMINAL:
      do_cmd_reset_remote_terminal();
      if(broadcast)
        return;
      send_response(STATUS_WORD);
      break;

    case CMD_TRANSMIT_VECTOR_WORD:
      if(broadcast)
        // Reset transaction
        return;
      send_response(STATUS_WORD);
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
      send_response(STATUS_WORD);
      send_tx_word(1,0xXXXX);
      break;

    case CMD_TRANSMIT_BUILT_IN_TEST_WORD:
      if(broadcast)
        // Reset transaction
        return;
      send_response(STATUS_WORD);
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

void send_response(uint16_t STATUS_WORD){
  response_gap(12);
  send_tx_word(0,STATUS_WORD);
  while(tx_word_empty() == 0){
    // NOP
  }
}

