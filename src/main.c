
#include <stdio.h>
#include <stdlib.h>

#include "ctrl_regs.h"
#include "rcv.h"

int main (){

  // CONFIG MODE
  // SET RT ADDRESS
  // ENABLE RECEIVER AND TRANSMITTER

  // START MESSAGE PROCESSOR UNIT
  //rt_msg_processor();

  printf("0x%d\n",RCV_CONTROL_REG_ENABLE_GET(0));

  return 0;
}

