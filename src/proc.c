
#include "ctrl_regs.h"
#include "mil_std.h"

volatile rx_msg_info_t rx_msg_info;

void msg_processor_unit() {

  while(1){

    while(rx_word_empty()){
      // NOP
    }

    get_rx_word(rx_msg_info);

    if(rx_msg_info.errors){
      // DO STUFF
      ERROR();
      continue;
    }

    if(rx_msg_info.status != COMMAND_WORD)
      continue;

    if((rx_msg_info.word & SUB_ADDR_MASK) == MODE_CODE_ADDR0)
      mode_code_fsm();
    else
      if((rx_msg_info.word & SUB_ADDR_MASK) == MODE_CODE_ADDR1)
        mode_code_fsm();
      else
        if(rx_msg_info.word & DIR_MASK)
          transmit_fsm();
        else
          receive_fsm();

    if(min_inter_msg_gap_timeout())
      // Minimum timeout not hold!

  }
}

