
#include "ctrl_regs.h"
#include "mil_std.h"

#define RT_ADDR_MASK        (0xF800)
#define DIR_MASK            (0x0400)
#define SUB_ADDR_MASK       (0x03e0)
#define MODE_CODE_MASK      (0x041F)

#define BROADCAST_ADDR      (31<< 11)
#define MODE_CODE_ADDR0     (0 << 5)
#define MODE_CODE_ADDR1     (31<< 5)

#define COMMAND_WORD        (0x0)
#define DATA_WORD           (0x1)
#define STATUS_WORD         (0x0)

volatile unsigned int rx_msg_available;
volatile unsigned int tx_msg_send;

void rx_irq_handler() {
  IRQ_DISABLE_ALL();
  IRQ_CLEAR();
  rx_msg_available = 1;
}

void tx_irq_handler() {
  IRQ_DISABLE_ALL();
  IRQ_CLEAR();
  tx_msg_send = 1;
}

volatile unsigned short STATUS_WORD       = 0x0000;
volatile unsigned short RESPONSE_SUPPRESS = 0;

volatile rx_msg_info_t rx_msg_info;
volatile tx_msg_info_t tx_msg_info;

enum State {IDLE_S, };

volatile State current_state;

void msg_processor_unit() {

  alt_irq_register(MIL_STD_XMT);
  alt_irq_register(MIL_STD_RCV);

  RX_IRQ_EN();

  current_state = IDLE_S;

  while(1){

    if(rx_msg_available){
      unsigned short int irq_vector = RCV_IRQ_VECTOR_GET();
      rx_msg_info.word    = RCV_DATA_WORD_GET();
      rx_msg_info.status  = RCV_DATA_STATUS_GET();
      rx_msg_info.errors  = RCV_DATA_ERRORS_GET();
    }

    if(rx_msg_available || tx_msg_send){

      switch(current_state){

        case IDLE_S:

          errors    = (rx_msg_info.errors != 0);
          cmd       = (rx_msg_info.status & 0x1) == (COMMAND_WORD);

          if(errors)
            continue;
          if(cmd == DATA_WORD)
            continue;

          broadcast = (rx_msg_info.word & RT_ADDR_MASK) == (BROADCAST_ADDR);
          usercast  = (rx_msg_info.word & RT_ADDR_MASK) == (BASIC_STATUS_GET() & RT_ADDR_MASK);

          if(((rx_msg_info.word & SUB_ADDR_MASK) == MODE_CODE_ADDR0) ||
             ((rx_msg_info.word & SUB_ADDR_MASK) == MODE_CODE_ADDR1))
            current_state = mode_code_fsm();
          else
            if(rx_msg_info.word & DIR_MASK)
              current_state = transmit_fsm();
            else
              current_state = receive_fsm();
          }

        case UNKNOWN_S:
          // ALARM!!!
      }

    WAIT_S:
      current_state = WAIT_S;

    SEND_RESPONSE:

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

