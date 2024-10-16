
#include <xmt.h>

void wait_tx_word(unsigned short* BASE_ADDR){
  XMT_IRQ_VECTOR_SET(BASE_ADDR,0x1);
  // Polling of XMT word valid bit
  while(1){
    unsigned short irq_vector_reg = XMT_IRQ_VECTOR_GET(BASE_ADDR);
    if(!XMT_IRQ_VECTOR_TRS_GET(irq_vector_reg))
      break;
  }
}

void send_tx_word(unsigned short* BASE_ADDR, tx_msg_info_t* msg_info) {

  XMT_DATA_WORD_SET(BASE_ADDR,msg_info -> data);
  XMT_DATA_STATUS_SET(BASE_ADDR,msg_info -> msg_type);

}

