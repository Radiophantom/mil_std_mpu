
#include <stdio.h>
#include <stdlib.h>

#include "ctrl_regs.h"

int main (){

  short *ptr;
  short *rd_ptr;
  short *wr_ptr;

  ptr = (short*)malloc(64);

  IOWR_CONTROL_REG              (ptr,CONTROL_REG_IRE(1));
  IOWR_RT_MSG_PTR_TABLE_ADDR_REG(ptr,RT_MSG_PTR_TABLE_ADDR(0x12345678));
  IOWR_BASIC_STATUS_REG         (ptr,BASIC_STATUS_REG_RT_ADDR(21));

  rd_ptr = ptr;
  printf("After any modifying!\n");
  for(int i = 0; i < 32; i++){
    printf("%d: 0x%hX\n",i,*rd_ptr++);
  }

  return 0;
}

//#include "ctrl_regs.h"
//
//static int state;
//
//static int rx_data_valid;
//
//static struct {
//  short data;
//  short status;
//  int   time_tag;
//} rx_data;
//
//void msg_receive_interrupt_handler(){
//  // Reset interrupt request
//  *(short unsigned*)(RCV_MSG_REG) = 0x01;
//  rx_data.data      = RD_MSG_DATA;
//  rx_data.status    = RD_MSG_STATUS;
//  rx_data.time_tag  = (RD_MSG_TIME_TAGH << 16) | RD_MSG_TIME_TAGL;
//  rx_data_valid     = 1;
//}
//
//#define RT_ADDR (BASIC_STATUS_REG >> 11)
//
//int main() {
//
//  register(msg_receive_interrupt_handler);
//
//  while(1) {
//
//    switch(state) {
//
//      IDLE_S:
//            parse_msg(rx_data,&parse_info);
//        if(rx_data.status & CMD_BITS == COMMAND){
//          if(rx_data.data & RT_ADDR_MSK == RT_ADDR){
//
//          }
//
//
//  }
//
//  return 0;
//}
//
