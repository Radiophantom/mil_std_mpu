
#include "ctrl_regs.h"
#include "mil_std.h"

volatile unsigned int rx_msg_available;
volatile unsigned int tx_msg_send;

void rx_irq_handler() {
  IRQ_DISABLE_ALL();
  rx_msg_available = 1;
}

void tx_irq_handler() {
  IRQ_DISABLE_ALL();
  tx_msg_send = 1;
}

volatile unsigned short STATUS_WORD       = 0x0000;
volatile unsigned short RESPONSE_SUPPRESS = 0;

volatile unsigned char usercast;
volatile unsigned char broadcast;
volatile unsigned char mode_code;

void transmit_fsm () {

  unsigned short* rt_msg_table_addr  = RT_MSG_PTR_TABLE_ADDR_GET(BASE_ADDR);
  cmd_msg_table_addr = rt_msg_table_addr+64+rx_msg_info.sub_address*2;

  TRANSMIT_S:
    // DO STUFF
    set_status_reg(0x0);
    WAIT_S;

  TRANSMIT_DATA_S:
    if(words_cnt == msg.words_cnt)
      IDLE_S;

  for(int i = 0; i < main_msg_info.words_cnt; i++){
    //
    tx_msg_info.msg_type  = 0x1;
    tx_msg_info.data      = tx_data--;
    send_tx_word(BASE_ADDR,&tx_msg_info);
  }
}

void mode_code_fsm () {

  unsigned short* rt_msg_table_addr  = RT_MSG_PTR_TABLE_ADDR_GET(BASE_ADDR);
  cmd_msg_table_addr = rt_msg_table_addr+32+rx_msg_info.sub_address*2;

  int mode_code_op = mode_code_valid(mcode);

  if(mode_code_op == -1)
    // DO STUFF
    SKIP_S;

  MODE_CODE_S:
    if(mode_code_op & EXTRA_DATA)
      // DO STUFF
      if(mode_code_op & BROADCAST)
        IDLE_S;
      else
        WAIT_S;
    else
      if(cmd == TRANSMIT)
        WAIT_S;
      else
        RECEIVE_MODE_CODE_DATA_S;

  TRANSMIT_MODE_CODE_DATA_S:
    IDLE_S;

  RECEIVE_MODE_CODE_DATA_S:
    if(cmd != DATA)
      // ERROR
    else
      // DO STUFF
      if(broadcast)
        IDLE_S;
      else
        WAIT_S;
}

void receive_fsm () {

  unsigned short* rt_msg_table_addr  = RT_MSG_PTR_TABLE_ADDR_GET(BASE_ADDR);
  cmd_msg_table_addr = rt_msg_table_addr+0+rx_msg_info.sub_address*2;

  RECEIVE_S:
    RECEIVE_FIRST_WORD_S;
  
  RECEIVE_FIRST_WORD_S:
    if(cmd == RECEIVE)
      // ERROR
    else if(cmd == TRANSMIT)
      RT_RT_OP_S;
    else
      RECEIVE_DATA_S;

  RECEIVE_DATA_S:
    if(cmd != DATA)
      // ERROR
    else
      if(words_cnt == msg.words_cnt)
        // DO STUFF
        if(broadcast)
          IDLE_S;
        else
          WAIT_S;

  for(int i = 0; i < main_msg_info.words_cnt; i++){
    //
    tx_msg_info.msg_type  = 0x1;
    tx_msg_info.data      = tx_data--;
    send_tx_word(BASE_ADDR,&tx_msg_info);
  }
}

void main_fsm () {

  IDLE_S:
    if(msg_received){
      if(msg_invalid)
        // DO STUFF
        SKIP_S;
      else
        if(cmd == DATA)
          // DO STUFF
          SKIP_S;
        if(check_addr() == OK)
          if(mode_code == true)
            mode_code_fsm();
          else if(cmd == RECEIVE)
            receive_fsm();
          else
            transmit_fsm();
    }

  WAIT_S:
    if(gap_cnt == response_cnt)
      SEND_RESPONSE;

  SEND_RESPONSE:
    if(cmd == TRANSMIT)
      TRANSMIT_DATA_S;
    else if(cmd == RECEIVE_S)
      IDLE_S;
    else if(cmd == MODE_CODE_S)
      IDLE_S;
    WAIT_S:
      if(gap_cnt == IFG)
        SEND_RESPONSE;

    tx_msg_info.msg_type  = 0x0;
    tx_msg_info.data      = STATUS_WORD;

    send_tx_word(BASE_ADDR,&tx_msg_info);
    wait_tx_word(BASE_ADDR);
}

#define RT_ADDR_MASK        (0x1F << 11 )
#define SUB_ADDR_MASK       (0x1F << 5  )

#define BROADCAST_ADDR      (31   << 11 )
#define MODE_CODE_ADDR0     (0    << 5  )
#define MODE_CODE_ADDR1     (31   << 5  )

#define COMMAND_WORD    (0x0)
#define DATA_WORD       (0x1)
#define STATUS_WORD     (0x0)

volatile rx_msg_info_t rx_msg_info;
volatile tx_msg_info_t tx_msg_info;

volatile int current_state;

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
          cmd       = (rx_msg_info.status & 0x1) == (COMMAND_WORD || STATUS_WORD);

          if(errors)
            continue;
          if(cmd == DATA_WORD)
            continue;

          broadcast = (rx_msg_info.word & RT_ADDR_MASK) == (BROADCAST_ADDR);
          usercast  = (rx_msg_info.word & RT_ADDR_MASK) == (BASIC_STATUS_GET() & RT_ADDR_MASK);

          if(((rx_msg_info.word & SUB_ADDR_MASK) == MODE_CODE_ADDR0) ||
             ((rx_msg_info.word & SUB_ADDR_MASK) == MODE_CODE_ADDR1))
            mode_code_fsm();
          else
            if((rx_msg_info.word & CMD_MASK) == (1<<10))
              transmit_fsm();
            else
              receive_fsm();
          }

        case UNKNOWN_S:
          // ALARM!!!
      }
    }

    unsigned short* rt_msg_table_addr  = RT_MSG_PTR_TABLE_ADDR_GET(BASE_ADDR);
    unsigned short* cmd_msg_table_addr;

  }

}

