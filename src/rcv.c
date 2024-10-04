
#include "rcv.h"

typedef struct {
  unsigned char   msg_type;
  unsigned char   rt_address;
  unsigned char   cmd; // 0 - RECEIVE, 1 - TRANSMIT
  unsigned char   sub_address;
  unsigned char   words_cnt;
  unsigned char   broadcast;
  unsigned char   unicast;
  unsigned char   mode_code;
  unsigned char   mode_code_err;
  unsigned char   mode_code_wdata;
  unsigned int    timestamp;
} rx_msg_info_t;

void wait_msg(){
  // Polling of RCV message valid bit
  while(1){
    unsigned short control_reg = IORD_CONTROL_REG(BASE_ADDR);
    if(CONTROL_REG_VALID_GET(control_reg))
      break;
  }
}

unsigned char mode_code_invalid (msg_info_t* msg_info){
    if( msg_info.word_count > 8 && msg_info.word_count < 16 )
      return 1;
  return 0;
}

void receive_word(rx_msg_info_t* msg_info){

  unsigned short sync_reg;
  unsigned short data_reg;
  unsigned short timestamp_regl;
  unsigned short timestamp_regh;
  unsigned short error_reg;

  wait_msg();

  sync_reg      = CONTROL_REG_SYNC_GET(IORD_CONTROL_REG(BASE_ADDR));
  data_reg      = IORD_DATA_REG(BASE_ADDR);
  error_reg     = IORD_ERRORS_REG(BASE_ADDR);

  msg_info -> timestamp       = (IORD_TIMESTAMPH_REG(BASE_ADDR) << 16) | IORD_TIMESTAMPL_REG(BASE_ADDR);

  msg_info -> msg_type        = sync_reg;
  msg_info -> rt_address      = _GET_BITS(data_reg,0x1F,11);
  msg_info -> cmd             = _GET_BITS(data_reg,0x1,10);
  msg_info -> sub_address     = _GET_BITS(data_reg,0x1F,5);
  msg_info -> word_count      = _GET_BITS(data_reg,0x1F,0);

  msg_info -> broadcast       = (msg_info.rt_address == 31);
  msg_info -> unicast         = (msg_info.rt_address == RT_ADDR);
  msg_info -> mode_code       = (msg_info.sub_addr == 0) || (msg_info.sub_addr == 31);
  msg_info -> mode_code_err   = mode_code_invalid(&msg_info);
  msg_info -> mode_code_wdata = (msg_info.word_count >> 4);
}

#endif

