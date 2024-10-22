
#ifndef __MODE_CODE_H__
#define __MODE_CODE_H__

#define CMD_DYNAMIC_BUS_CONTROL                 0x400 // Not implemented
#define CMD_SYNCHRONIZE                         0x401
#define CMD_TRANSMIT_STATUS_WORD                0x402 // Not implemented
#define CMD_INITIATE_SELF_TEST                  0x403 // Not implemented
#define CMD_TRANSMITTER_SHUTDOWN                0x404 // Not implemented
#define CMD_OVERRIDE_TRANSMITTER_SHUTDOWN       0x405 // Not implemented
#define CMD_INHIBIT_TERMINAL_FLAG_BIT           0x406 // Not implemented
#define CMD_OVERRIDE_INHIBIT_TERMINAL_FLAG_BIT  0x407 // Not implemented
#define CMD_RESET_REMOTE_TERMINAL               0x408
#define CMD_TRANSMIT_VECTOR_WORD                0x410
#define CMD_SYNCHRONIZE_WITH_DATA_WORD          0x011
#define CMD_TRANSMIT_LAST_COMMAND_WORD          0x412 // Not implemented
#define CMD_TRANSMIT_BUILT_IN_TEST_WORD         0x413 // Not implemented
#define CMD_SELECTED_TRANSMITTER                0x014 // Not implemented
#define CMD_OVERRIDE_SELECTED_TRANSMITTER       0x015 // Not implemented

#define BROADCAST  (1 << 0)
#define EXTRA_DATA (1 << 1)

// return value - [DATA + BROADCAST] bits.
// Valid combinations [00;01;10;11].
int mode_code_valid(int mode_code) {
  switch(mode_code)
    case CMD_DYNAMIC_BUS_CONTROL:                 return 0;
    case CMD_SYNCHRONIZE:                         return (BROADCAST);
    case CMD_TRANSMIT_STATUS_WORD:                return 0;
    case CMD_INITIATE_SELF_TEST:                  return (BROADCAST);
    case CMD_TRANSMITTER_SHUTDOWN:                return (BROADCAST);
    case CMD_OVERRIDE_TRANSMITTER_SHUTDOWN:       return (BROADCAST);
    case CMD_INHIBIT_TERMINAL_FLAG_BIT:           return (BROADCAST);
    case CMD_OVERRIDE_INHIBIT_TERMINAL_FLAG_BIT:  return (BROADCAST);
    case CMD_RESET_REMOTE_TERMINAL:               return (BROADCAST);
    case CMD_TRANSMIT_VECTOR_WORD:                return (EXTRA_DATA);
    case CMD_SYNCHRONIZE_WITH_DATA_WORD:          return (BROADCAST | EXTRA_DATA);
    case CMD_TRANSMIT_LAST_COMMAND_WORD:          return (EXTRA_DATA);
    case CMD_TRANSMIT_BUILT_IN_TEST_WORD:         return (EXTRA_DATA);
    case CMD_SELECTED_TRANSMITTER:                return (BROADCAST | EXTRA_DATA);
    case CMD_OVERRIDE_SELECTED_TRANSMITTER:       return (BROADCAST | EXTRA_DATA);
  return -1;
}

#endif

