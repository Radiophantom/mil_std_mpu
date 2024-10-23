
#include "mode_code.h"

void ERROR(){
  // Do some error processing things.
}

rx_msg_info_t ctrl_msg_info;

#define BROADCAST_MSG(data) ((data && RT_ADDR_MASK) == BROADCAST_ADDR)

State mode_code_fsm(){

  switch(current_state){

    MODE_CODE_S:

      switch(rx_msg_info.word & MODE_CODE_MASK){

        case CMD_DYNAMIC_BUS_CONTROL:
          if(BROADCAST_MSG(rx_msg_info.word))
            ERROR(); return IDLE_S;
          do_cmd_dynamic_bus_control();
          return SEND_RESPONSE_S;

        case CMD_SYNCHRONIZE:
          do_cmd_synchronize();
          if(BROADCAST_MSG(rx_msg_info.word))
            current_state = IDLE_S;
          else
            current_state = SEND_RESPONSE_S;
          return;

        case CMD_TRANSMIT_STATUS_WORD:
          if(BROADCAST_MSG(rx_msg_info.word))
            ERROR(); break;
          do_cmd_transmit_status_word();
          current_state = SEND_RESPONSE_S;
          return;

        case CMD_INITIATE_SELF_TEST:
          do_cmd_initiate_self_test();
          if(BROADCAST_MSG(rx_msg_info.word))
            current_state = IDLE_S;
          else
            current_state = SEND_RESPONSE_S;
          return;

        case CMD_TRANSMITTER_SHUTDOWN:
          do_cmd_transmitter_shutdown();
          if(BROADCAST_MSG(rx_msg_info.word))
            current_state = IDLE_S;
          else
            current_state = SEND_RESPONSE_S;
          return;

        case CMD_OVERRIDE_TRANSMITTER_SHUTDOWN:
          do_cmd_override_transmitter_shutdown();
          if(BROADCAST_MSG(rx_msg_info.word))
            current_state = IDLE_S;
          else
            current_state = SEND_RESPONSE_S;
          return;

        case CMD_INHIBIT_TERMINAL_FLAG_BIT:
          do_cmd_inhibit_terminal_flag_bit();
          if(BROADCAST_MSG(rx_msg_info.word))
            current_state = IDLE_S;
          else
            current_state = SEND_RESPONSE_S;
          return;

        case CMD_OVERRIDE_INHIBIT_TERMINAL_FLAG_BIT:
          do_cmd_override_inhibit_terminal_flag_bit();
          if(BROADCAST_MSG(rx_msg_info.word))
            current_state = IDLE_S;
          else
            current_state = SEND_RESPONSE_S;
          return;

        case CMD_RESET_REMOTE_TERMINAL:
          do_cmd_reset_remote_terminal();
          if(BROADCAST_MSG(rx_msg_info.word))
            current_state = IDLE_S;
          else
            current_state = SEND_RESPONSE_S;
          return;

        case CMD_TRANSMIT_VECTOR_WORD:
          if(BROADCAST_MSG(rx_msg_info.word))
            ERROR(); break;
          current_state = SEND_EXTRA_WORD_S;
          return;

        case CMD_SYNCHRONIZE_WITH_DATA_WORD:
          current_state = RCV_EXTRA_WORD_S;
          return;

        case CMD_TRANSMIT_LAST_COMMAND_WORD:
          if(BROADCAST_MSG(rx_msg_info.word))
            ERROR(); break;
          current_state = SEND_EXTRA_WORD_S;
          return;

        case CMD_TRANSMIT_BUILT_IN_TEST_WORD:
          if(BROADCAST_MSG(rx_msg_info.word))
            ERROR(); break;
          current_state = SEND_EXTRA_WORD_S;
          return;

        case CMD_SELECTED_TRANSMITTER:
          current_state = RCV_EXTRA_WORD_S;
          return;

        case CMD_OVERRIDE_SELECTED_TRANSMITTER:
          current_state = RCV_EXTRA_WORD_S;
          return;

        default:
          current_state = IDLE_S;
          return;
      }
    }

    RCV_EXTRA_WORD_S:
      switch(mode_code){
        case CMD_SYNCHRONIZE_WITH_DATA_WORD:
          do_cmd_synchronize_with_data_word();
          if(BROADCAST_MSG(rx_msg_info.word))
            current_state = IDLE_S;
          return;

        case CMD_SELECTED_TRANSMITTER:
          do_cmd_selected_transmitter();
          if(BROADCAST_MSG(rx_msg_info.word))
            current_state = IDLE_S;
          return;

        case CMD_OVERRIDE_SELECTED_TRANSMITTER:
          do_cmd_override_selected_transmitter();
          if(BROADCAST_MSG(rx_msg_info.word))
            current_state = IDLE_S;
          return;
      }

    SEND_EXTRA_WORD_S:
      switch(mode_code){
        case CMD_TRANSMIT_VECTOR_WORD:
          do_cmd_transmit_vector_word();
          current_state = IDLE_S;
          return;
        case CMD_TRANSMIT_LAST_COMMAND_WORD:
          do_cmd_transmit_last_command_word();
          current_state = IDLE_S;
          return;
        case CMD_TRANSMIT_BUILT_IN_TEST_WORD:
          do_cmd_transmit_built_in_test_word();
          current_state = IDLE_S;
          return;
      }
  }

}

void do_cmd_dynamic_bus_control(){

  unsigned short* rt_msg_table_addr;
  unsigned short* mcode_msg_table_addr;

  rt_msg_table_addr = (unsigned short*)RT_MSG_PTR_TABLE_ADDR_GET();
  mcode_msg_table_addr = rt_msg_table_addr+32+(rx_msg_info.word & SUB_ADDR_MASK);

}

