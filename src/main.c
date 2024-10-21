
#include <stdio.h>
#include <stdlib.h>

#include "proc.h"

#define MIL_STD_CONTROLLER_BASE 0x60000

int main (){

  // CONFIG MODE
  write(CFG1, UNDEFINED_MODE);

  // SET RT ADDRESS
  read(MIL_STD_RT_ADDR);

  // ENABLE RECEIVER AND TRANSMITTER
  write(MIL_STD_ENABLE, (1<<0) | (1<<1));

  // Register some interrupts
  alt_irq_register(RESET_REG,reset_vector);
  alt_irq_register(MODE_REG,mode_vector);
  alt_irq_register(MIL_STD_XMT);
  alt_irq_register(MIL_STD_RCV);

  // LAUNCH MESSAGE PROCESSOR UNIT
  msg_processor_unit();

  return 0;
}

