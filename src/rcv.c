
#include "rcv.h"

void wait_rx_word(unsigned short* BASE_ADDR){
  // Polling of RCV word valid bit
  while(1){
    unsigned short irq_vector_reg = RCV_IRQ_VECTOR_GET(BASE_ADDR);
    if(RCV_IRQ_VECTOR_RCV_GET(irq_vector_reg))
      break;
  }
}

void get_rx_word(unsigned short* BASE_ADDR, rx_msg_info_t* msg_info) {

  wait_rx_word(BASE_ADDR);

  unsigned short data_word_reg    = RCV_DATA_WORD_GET(BASE_ADDR);
  unsigned short data_status_reg  = RCV_DATA_STATUS_GET(BASE_ADDR);
  unsigned short data_errors_reg  = RCV_DATA_ERRORS_GET(BASE_ADDR);

  msg_info -> msg_type    = (data_status_reg  >> 0 ) & 0x01;
  msg_info -> rt_address  = (data_word_reg    >> 11) & 0x1F;
  msg_info -> cmd         = (data_word_reg    >> 10) & 0x01;
  msg_info -> sub_address = (data_word_reg    >> 5 ) & 0x1F;
  msg_info -> words_cnt   = (data_word_reg    >> 0 ) & 0x1F;
  msg_info -> data        = data_word_reg;

  if(msg_info -> words_cnt == 0)
    msg_info -> words_cnt = 32;

  RCV_IRQ_VECTOR_SET(BASE_ADDR,0x0);

}

//unsigned char mode_code_invalid (msg_info_t* msg_info){
//    if( msg_info.word_count > 8 && msg_info.word_count < 16 )
//      return 1;
//  return 0;
//}
//
//void receive_word(rx_msg_info_t* msg_info){
//
//  unsigned short data_word_reg;
//  unsigned short data_status_reg;
//  unsigned short data_errors_reg;
//
//  wait_rx_word();
//
//  data_word_reg   = RCV_DATA_WORD_GET(BASE_ADDR);
//  data_status_reg = RCV_DATA_STATUS_GET(BASE_ADDR);
//  data_errors_reg = RCV_DATA_ERRORS_GET(BASE_ADDR);
//
//  msg_info -> msg_type        = RCV_DATA_STATUS_SYNC_C_GET(data_status_reg);
//  msg_info -> rt_address      = _GET_BITS(data_status_reg,0x1F,11);
//  msg_info -> cmd             = _GET_BITS(data_status_reg,0x1,10);
//  msg_info -> sub_address     = _GET_BITS(data_status_reg,0x1F,5);
//  msg_info -> word_count      = _GET_BITS(data_status_reg,0x1F,0);
//
//  msg_info -> broadcast       = (msg_info -> rt_address == 31);
//  //msg_info -> unicast         = (msg_info -> rt_address == RT_ADDR_GET(BASE_ADDR));
//  msg_info -> mode_code       = (msg_info -> sub_addr == 0) || (msg_info -> sub_addr == 31);
//  //msg_info -> mode_code_err   = mode_code_invalid(&msg_info);
//  msg_info -> mode_code_wdata = (msg_info.word_count >> 4);
//}

