
#ifndef __RCV_H__
#define __RCV_H__

#include "ctrl_regs.h"
#include "mil_std.h"

typedef struct {
  unsigned short data_status;
  unsigned short data_word;
  unsigned short data_errors;
} rx_msg_info_t;

typedef struct {
  unsigned char   rt_address;
  unsigned char   cmd; // 0 - RECEIVE, 1 - TRANSMIT
  unsigned char   sub_address;
  unsigned char   words_cnt;
} rx_cmd_t;

typedef struct {
  unsigned char   rt_address;
  unsigned char   cmd; // 0 - RECEIVE, 1 - TRANSMIT
  unsigned char   sub_address;
  unsigned char   mode_code;
} rx_mode_code_t;

typedef struct {
  unsigned short  data;
} rx_data_t;

typedef struct {
  unsigned char   msg_type;
  unsigned char   rt_address;
  unsigned char   cmd; // 0 - RECEIVE, 1 - TRANSMIT
  unsigned char   sub_address;
  unsigned char   words_cnt;
  unsigned short  data;
} rx_msg_info_t;

void get_rx_word(unsigned short* BASE_ADDR, rx_msg_info_t* msg_info);

//typedef struct {
//  unsigned char   msg_type;
//  unsigned char   rt_address;
//  unsigned char   cmd; // 0 - RECEIVE, 1 - TRANSMIT
//  unsigned char   sub_address;
//  unsigned char   words_cnt;
//  unsigned char   broadcast;
//  unsigned char   unicast;
//  unsigned char   mode_code;
//  unsigned char   mode_code_err;
//  unsigned char   mode_code_wdata;
//  unsigned int    timestamp;
//} rx_msg_info_t;

#endif

