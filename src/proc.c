
#include "ctrl_regs.h"
#include "mil_std.h"

#define RT_ADDR_MASK        (0xF800)
#define DIR_MASK            (0x0400)
#define SUB_ADDR_MASK       (0x03e0)
#define MODE_CODE_MASK      (0x041F)

#define BROADCAST_ADDR      (31<< 11)
#define MODE_CODE_ADDR0     (0 << 5)
#define MODE_CODE_ADDR1     (31<< 5)

//#define DIR_RECEIVE         (0x0000)
//#define DIR_TRANSMIT        (0x0400)

#define COMMAND_WORD        (0x0)
#define DATA_WORD           (0x1)
#define STATUS_WORD         (0x0)

//void rx_irq_handler() {
//  IRQ_DISABLE_ALL();
//  IRQ_CLEAR();
//  rx_msg_available = 1;
//}
//
//void tx_irq_handler() {
//  IRQ_DISABLE_ALL();
//  IRQ_CLEAR();
//  tx_msg_send = 1;
//}

volatile unsigned short STATUS_WORD       = 0x0000;
volatile unsigned short RESPONSE_SUPPRESS = 0;

volatile rx_msg_info_t rx_msg_info;
volatile tx_msg_info_t tx_msg_info;

enum State {IDLE_S, };

volatile State current_state;

void msg_processor_unit() {

  current_state = IDLE_S;

  while(1){

      switch(current_state){

        case IDLE_S:

          while(rx_word_available() == 0){
            // NOP
          }

          get_rx_word(rx_msg_info);

          if(rx_msg_info.errors){
            // DO STUFF
            ERROR();
            current_state = IDLE_S;
            continue;
          }

          if(rx_msg_info.status != COMMAND_WORD)
            continue;

          if(((rx_msg_info.word & SUB_ADDR_MASK) == MODE_CODE_ADDR0) ||
             ((rx_msg_info.word & SUB_ADDR_MASK) == MODE_CODE_ADDR1))
            current_state = mode_code_fsm();
          else
            if(rx_msg_info.word & DIR_MASK)
              current_state = transmit_fsm();
            else
              current_state = receive_fsm();

        case WAIT_S:
          current_state = WAIT_S;

        case SEND_RESPONSE:

          WAIT_S;

          tx_msg_info.msg_type  = 0x0;
          tx_msg_info.data      = STATUS_WORD;

          send_tx_word(&tx_msg_info);

          if(EXTRA_WORD_S)
            current_state = MODE_CODE_S;
          else
            if(rx_msg_info.word & DIR_MASK)
              current_state = TRANSMIT_DATA_S;
            else
              current_state = RECEIVE_S;
      }
}

