
#include "proc.h"

void rt_msg_processor(unsigned short* BASE_ADDR) {

  rx_msg_info_t main_msg_info;

  rx_msg_info_t rx_msg_info;
  tx_msg_info_t tx_msg_info;

  while(1){

    get_rx_word(BASE_ADDR,&main_msg_info);

    if(main_msg_info.cmd == 0){

      for(int i = 0; i < main_msg_info.words_cnt; i++ ){
        get_rx_word(BASE_ADDR,&rx_msg_info);
      }

      tx_msg_info.msg_type  = 0x1;
      tx_msg_info.data      = (main_msg_info.rt_address << 11);

      send_tx_word(BASE_ADDR,&tx_msg_info);

    } else {

      tx_msg_info.msg_type  = 0x1;
      tx_msg_info.data      = (main_msg_info.rt_address << 11);

      send_tx_word(BASE_ADDR,&tx_msg_info);

      unsigned short tx_data = 0xFF;

      for(int i = 0; i < main_msg_info.words_cnt; i++){
        tx_msg_info.msg_type  = 0x0;
        tx_msg_info.data      = tx_data--;
        send_tx_word(BASE_ADDR,&tx_msg_info);
      }
    }
  }
}

////typedef struct {
////  unsigned char   rt_address;
////  unsigned char   msg_error;
////  //unsigned char   instr_bit;
////  //unsigned char   service_req;
////  unsigned char   bcst_rcvd;
////  //unsigned char   busy;
////  //unsigned char   subsys_flag;
////  //unsigned char   dyn_bus_accept;
////  //unsigned char   terminal_flag;
////} stat_data_t;
////
////typedef struct {
////  unsigned char   msg_type; // 0 - COMMAND, 1 - DATA
////  unsigned short  msg_data;
////} tx_msg_info_t;
//
//void rt_msg_processor(){
//
//  rx_msg_info_t rx_msg_info;
//  tx_msg_info_t tx_msg_info;
//
//  while(1){
//
//    receive_word(rx_msg_info);
//
//    if(rx_msg_info.cmd == 0){
//      // Receive command
//      if(rx_msg_info.mode_code){
//        // Mode code command
//        if(rx_msg_info.mode_code_wdata){
//          receive_word();
//        }
//      } else {
//        // Receive data command
//        receive_word();
//        if(rx_msg_info.cmd == 1){
//          // RT - RT transaction
//          receive_word();
//        }
//        unsigned char word_cnt = (rx_msg_info.word_cnt == 0) ? 32 : rx_msg_info.word_cnt;
//        while(word_cnt){
//          receive_word();
//          word_cnt--;
//        }
//      }
//      if(rx_msg_info.broadcast){
//        // SKIP status word
//      } else {
//        wait_gap();
//        send_status_word();
//      }
//    } else {
//      // Transmit command
//      wait_gap();
//      send_status_word();
//      if(rx_msg_info.mode_code){
//        transmit_word();
//      } else {
//        unsigned char word_cnt = (rx_msg_info.word_cnt == 0) ? 32 : rx_msg_info.word_cnt;
//        while(word_cnt){
//          transmit_word();
//          word_cnt--;
//        }
//      }
//    }
//}
//
