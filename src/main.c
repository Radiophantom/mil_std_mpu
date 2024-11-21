
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "proc.h"
#include "rcv.h"
#include "xmt.h"

int main (){

  rx_word_t rx_word;

  // Enable receiver and transmitter
  RCV_CONTROL_SET(RCV_CONTROL_ENABLE);
  XMT_CONTROL_SET(XMT_CONTROL_ENABLE);

  while(1){

    while(get_rx_word(&rx_word,10)){
      // NOP
    }

    if(rx_word.word_errors){
      //TODO: Do some required stuff
      ERROR();
      continue;
    }

    if(rx_word.word_status != COMMAND_WORD)
      continue;

    if((rx_word.word_data & SUB_ADDR_MASK) == MODE_CODE_ADDR0)
      mode_code_msg(&rx_word);
    else
      if((rx_word.word_data & SUB_ADDR_MASK) == MODE_CODE_ADDR1)
        mode_code_msg(&rx_word);
      else
        if(rx_word.word_data & DIR_MASK)
          transmit_msg(&rx_word);
        else
          receive_msg(&rx_word);

    // TODO: Add check inter-message gap timeout
    //if(min_inter_msg_gap_timeout())
      // Minimum timeout not hold!

  }
  return 0;
}

