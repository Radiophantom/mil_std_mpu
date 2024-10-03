
#ifndef __CONTROL_REGS_H__
#define __CONTROL_REGS_H__

#define IORD(base,addr)       (*(unsigned short*)(base+addr))
#define IOWR(base,addr,data)  (*(unsigned short*)(base+addr) = data)

#define _SET_BITS(data,mask,offset)  ((data & mask) << offset)
#define _GET_BITS(data,mask,offset)  ((data >> offset) & mask)

#define CONTROL_REG                               0
#define IORD_CONTROL_REG(base)                    IORD(base,CONTROL_REG)
#define IOWR_CONTROL_REG(base,data)               IOWR(base,CONTROL_REG,data)
#define CONTROL_REG_IRE_MASK                      (0x1)
#define CONTROL_REG_IRE_OFST                      (7)
#define CONTROL_REG_IRE_SET(data)                 _SET_BITS(data,CONTROL_REG_IRE_MASK,CONTROL_REG_IRE_OFST)
#define CONTROL_REG_IRE_GET(data)                 _GET_BITS(data,CONTROL_REG_IRE_MASK,CONTROL_REG_IRE_OFST)

#define RT_MSG_PTR_TABLE_ADDR_REG                 1
#define IORD_RT_MSG_PTR_TABLE_ADDR_REG(base)      IORD(base,RT_MSG_PTR_TABLE_ADDR_REG)
#define IOWR_RT_MSG_PTR_TABLE_ADDR_REG(base,data) IOWR(base,RT_MSG_PTR_TABLE_ADDR_REG,data)
#define RT_MSG_PTR_TABLE_ADDR_MASK                (0xFFFF)
#define RT_MSG_PTR_TABLE_ADDR_OFST                (0)
#define RT_MSG_PTR_TABLE_ADDR_SET(data)           _SET_BITS(data,RT_MSG_PTR_TABLE_ADDR_MASK,RT_MSG_PTR_TABLE_ADDR_OFST)
#define RT_MSG_PTR_TABLE_ADDR_GET(data)           _GET_BITS(data,RT_MSG_PTR_TABLE_ADDR_MASK,RT_MSG_PTR_TABLE_ADDR_OFST)

#define BASIC_STATUS_REG                          2
#define IORD_BASIC_STATUS_REG(base)               IORD(base,BASIC_STATUS_REG)
#define IOWR_BASIC_STATUS_REG(base,data)          IOWR(base,BASIC_STATUS_REG,data)
#define BASIC_STATUS_REG_RT_ADDR_MASK             (0x1F)
#define BASIC_STATUS_REG_RT_ADDR_OFST             (11)
#define BASIC_STATUS_REG_RT_ADDR_SET(data)        _SET_BITS(data,BASIC_STATUS_REG_RT_ADDR_MASK,BASIC_STATUS_REG_RT_ADDR_OFST)
#define BASIC_STATUS_REG_RT_ADDR_GET(data)        _GET_BITS(data,BASIC_STATUS_REG_RT_ADDR_MASK,BASIC_STATUS_REG_RT_ADDR_OFST)

/*
#define INTERRUPT_MASKL_REG                     3
#define INTERRUPT_VECTORH_REG                   3
#define INTERRUPT_REQUESTH_REG                  3
#define INTERRUPT_VECTORL_REG                   4
#define AUX_VECTORH_REG                         4
#define CONFIG2H_REG                            4
#define RTC_HIGH_WORD_REG                       5
#define RTC_LOW_WORD_REG                        6
#define RTC_CONTROL_REG                         7
#define READ_FIFO_REG                           8
#define RESET_FIFO_REG                          8
#define CONFIG1_REG                             9
#define BC_CUR_MJR_MNR_FRM_INDX_REG             10
#define LAST_CMD_REG                            11
#define LAST_STATUS_REG                         12
#define MJR_FRM_A_ADDR_REG                      13
#define ASYNC_FRAME_ADDR_REG                    14
#define RESET_TERMINAL_REG                      15
#define MJR_FRM_B_ADDR_REG                      16
//#define RESERVED
#define ENCODER_STATUS_REG                      18
#define CONDITION_REG                           19
#define BCU_FRM_GAP_WORD_MTU_EOF_OPTIONS_REG    20
#define CONFIG3_REG                             21
#define MSG_MON_ADDRL_FILTER_REG                22
#define ENCODER_DATA_REG                        23
#define ENCODER_DATA_TX_REQ_REG                 24
#define ENCODER_CMD_TX_REQ_REG                  25
#define MSG_MON_ADDRH_FILTER_REG                26
#define BC_CUR_MNR_FRM_ADDR_REG                 27
#define CLEAR_REGISTER_27_REG                   27
#define MON_BLOCK_B_LAST_ADDR_REG               27
#define BC_CUR_MSG_ADDR_REG                     28
#define CLEAR_REGISTER_28_REG                   28
#define RT_LOG_PTR_TABLE_ADDR_REG               29
#define EXTERNAL_RTU_ADDR_BUFL_REG              30
#define BC_MU_IRQ_VECTOR_REG                    31

#define IO_RD_CONTROL_REG                             *(short unsigned *)(CONTROL_REG                         )
#define IO_RD_RT_MSG_PTR_TABLE_ADDR_REG               *(short unsigned *)(RT_MSG_PTR_TABLE_ADDR_REG           )
#define IO_RD_BASIC_STATUS_REG                        *(short unsigned *)(BASIC_STATUS_REG                    )
#define IO_RD_INTERRUPT_MASKL_REG                     *(short unsigned *)(INTERRUPT_MASKL_REG                 )
#define IO_RD_INTERRUPT_VECTORH_REG                   *(short unsigned *)(INTERRUPT_VECTORH_REG               )
#define IO_RD_INTERRUPT_REQUESTH_REG                  *(short unsigned *)(INTERRUPT_REQUESTH_REG              )
#define IO_RD_INTERRUPT_VECTORL_REG                   *(short unsigned *)(INTERRUPT_VECTORL_REG               )
#define IO_RD_AUX_VECTORH_REG                         *(short unsigned *)(AUX_VECTORH_REG                     )
#define IO_RD_CONFIG2H_REG                            *(short unsigned *)(CONFIG2H_REG                        )
#define IO_RD_RTC_HIGH_WORD_REG                       *(short unsigned *)(RTC_HIGH_WORD_REG                   )
#define IO_RD_RTC_LOW_WORD_REG                        *(short unsigned *)(RTC_LOW_WORD_REG                    )
#define IO_RD_RTC_CONTROL_REG                         *(short unsigned *)(RTC_CONTROL_REG                     )
#define IO_RD_READ_FIFO_REG                           *(short unsigned *)(READ_FIFO_REG                       )
#define IO_RD_RESET_FIFO_REG                          *(short unsigned *)(RESET_FIFO_REG                      )
#define IO_RD_CONFIG1_REG                             *(short unsigned *)(CONFIG1_REG                         )
#define IO_RD_BC_CUR_MJR_MNR_FRM_INDX_REG             *(short unsigned *)(BC_CUR_MJR_MNR_FRM_INDX_REG         )
#define IO_RD_LAST_CMD_REG                            *(short unsigned *)(LAST_CMD_REG                        )
#define IO_RD_LAST_STATUS_REG                         *(short unsigned *)(LAST_STATUS_REG                     )
#define IO_RD_MJR_FRM_A_ADDR_REG                      *(short unsigned *)(MJR_FRM_A_ADDR_REG                  )
#define IO_RD_ASYNC_FRAME_ADDR_REG                    *(short unsigned *)(ASYNC_FRAME_ADDR_REG                )
#define IO_RD_RESET_TERMINAL_REG                      *(short unsigned *)(RESET_TERMINAL_REG                  )
#define IO_RD_MJR_FRM_B_ADDR_REG                      *(short unsigned *)(MJR_FRM_B_ADDR_REG                  )
#define IO_RD_ENCODER_STATUS_REG                      *(short unsigned *)(ENCODER_STATUS_REG                  )
#define IO_RD_CONDITION_REG                           *(short unsigned *)(CONDITION_REG                       )
#define IO_RD_BCU_FRM_GAP_WORD_MTU_EOF_OPTIONS_REG    *(short unsigned *)(BCU_FRM_GAP_WORD_MTU_EOF_OPTIONS_REG)
#define IO_RD_CONFIG3_REG                             *(short unsigned *)(CONFIG3_REG                         )
#define IO_RD_MSG_MON_ADDRL_FILTER_REG                *(short unsigned *)(MSG_MON_ADDRL_FILTER_REG            )
#define IO_RD_ENCODER_DATA_REG                        *(short unsigned *)(ENCODER_DATA_REG                    )
#define IO_RD_ENCODER_DATA_TX_REQ_REG                 *(short unsigned *)(ENCODER_DATA_TX_REQ_REG             )
#define IO_RD_ENCODER_CMD_TX_REQ_REG                  *(short unsigned *)(ENCODER_CMD_TX_REQ_REG              )
#define IO_RD_MSG_MON_ADDRH_FILTER_REG                *(short unsigned *)(MSG_MON_ADDRH_FILTER_REG            )
#define IO_RD_BC_CUR_MNR_FRM_ADDR_REG                 *(short unsigned *)(BC_CUR_MNR_FRM_ADDR_REG             )
#define IO_RD_CLEAR_REGISTER_27_REG                   *(short unsigned *)(CLEAR_REGISTER_27_REG               )
#define IO_RD_MON_BLOCK_B_LAST_ADDR_REG               *(short unsigned *)(MON_BLOCK_B_LAST_ADDR_REG           )
#define IO_RD_BC_CUR_MSG_ADDR_REG                     *(short unsigned *)(BC_CUR_MSG_ADDR_REG                 )
#define IO_RD_CLEAR_REGISTER_28_REG                   *(short unsigned *)(CLEAR_REGISTER_28_REG               )
#define IO_RD_RT_LOG_PTR_TABLE_ADDR_REG               *(short unsigned *)(RT_LOG_PTR_TABLE_ADDR_REG           )
#define IO_RD_EXTERNAL_RTU_ADDR_BUFL_REG              *(short unsigned *)(EXTERNAL_RTU_ADDR_BUFL_REG          )
#define IO_RD_BC_MU_IRQ_VECTOR_REG                    *(short unsigned *)(BC_MU_IRQ_VECTOR_REG                )

#define IO_WR_CONTROL_REG(data)                             *(short unsigned *)(CONTROL_REG                         ) = data
#define IO_WR_RT_MSG_PTR_TABLE_ADDR_REG(data)               *(short unsigned *)(RT_MSG_PTR_TABLE_ADDR_REG           ) = data
#define IO_WR_BASIC_STATUS_REG(data)                        *(short unsigned *)(BASIC_STATUS_REG                    ) = data
#define IO_WR_INTERRUPT_MASKL_REG(data)                     *(short unsigned *)(INTERRUPT_MASKL_REG                 ) = data
#define IO_WR_INTERRUPT_VECTORH_REG(data)                   *(short unsigned *)(INTERRUPT_VECTORH_REG               ) = data
#define IO_WR_INTERRUPT_REQUESTH_REG(data)                  *(short unsigned *)(INTERRUPT_REQUESTH_REG              ) = data
#define IO_WR_INTERRUPT_VECTORL_REG(data)                   *(short unsigned *)(INTERRUPT_VECTORL_REG               ) = data
#define IO_WR_AUX_VECTORH_REG(data)                         *(short unsigned *)(AUX_VECTORH_REG                     ) = data
#define IO_WR_CONFIG2H_REG(data)                            *(short unsigned *)(CONFIG2H_REG                        ) = data
#define IO_WR_RTC_HIGH_WORD_REG(data)                       *(short unsigned *)(RTC_HIGH_WORD_REG                   ) = data
#define IO_WR_RTC_LOW_WORD_REG(data)                        *(short unsigned *)(RTC_LOW_WORD_REG                    ) = data
#define IO_WR_RTC_CONTROL_REG(data)                         *(short unsigned *)(RTC_CONTROL_REG                     ) = data
#define IO_WR_READ_FIFO_REG(data)                           *(short unsigned *)(READ_FIFO_REG                       ) = data
#define IO_WR_RESET_FIFO_REG(data)                          *(short unsigned *)(RESET_FIFO_REG                      ) = data
#define IO_WR_CONFIG1_REG(data)                             *(short unsigned *)(CONFIG1_REG                         ) = data
#define IO_WR_BC_CUR_MJR_MNR_FRM_INDX_REG(data)             *(short unsigned *)(BC_CUR_MJR_MNR_FRM_INDX_REG         ) = data
#define IO_WR_LAST_CMD_REG(data)                            *(short unsigned *)(LAST_CMD_REG                        ) = data
#define IO_WR_LAST_STATUS_REG(data)                         *(short unsigned *)(LAST_STATUS_REG                     ) = data
#define IO_WR_MJR_FRM_A_ADDR_REG(data)                      *(short unsigned *)(MJR_FRM_A_ADDR_REG                  ) = data
#define IO_WR_ASYNC_FRAME_ADDR_REG(data)                    *(short unsigned *)(ASYNC_FRAME_ADDR_REG                ) = data
#define IO_WR_RESET_TERMINAL_REG(data)                      *(short unsigned *)(RESET_TERMINAL_REG                  ) = data
#define IO_WR_MJR_FRM_B_ADDR_REG(data)                      *(short unsigned *)(MJR_FRM_B_ADDR_REG                  ) = data
#define IO_WR_ENCODER_STATUS_REG(data)                      *(short unsigned *)(ENCODER_STATUS_REG                  ) = data
#define IO_WR_CONDITION_REG(data)                           *(short unsigned *)(CONDITION_REG                       ) = data
#define IO_WR_BCU_FRM_GAP_WORD_MTU_EOF_OPTIONS_REG(data)    *(short unsigned *)(BCU_FRM_GAP_WORD_MTU_EOF_OPTIONS_REG) = data
#define IO_WR_CONFIG3_REG(data)                             *(short unsigned *)(CONFIG3_REG                         ) = data
#define IO_WR_MSG_MON_ADDRL_FILTER_REG(data)                *(short unsigned *)(MSG_MON_ADDRL_FILTER_REG            ) = data
#define IO_WR_ENCODER_DATA_REG(data)                        *(short unsigned *)(ENCODER_DATA_REG                    ) = data
#define IO_WR_ENCODER_DATA_TX_REQ_REG(data)                 *(short unsigned *)(ENCODER_DATA_TX_REQ_REG             ) = data
#define IO_WR_ENCODER_CMD_TX_REQ_REG(data)                  *(short unsigned *)(ENCODER_CMD_TX_REQ_REG              ) = data
#define IO_WR_MSG_MON_ADDRH_FILTER_REG(data)                *(short unsigned *)(MSG_MON_ADDRH_FILTER_REG            ) = data
#define IO_WR_BC_CUR_MNR_FRM_ADDR_REG(data)                 *(short unsigned *)(BC_CUR_MNR_FRM_ADDR_REG             ) = data
#define IO_WR_CLEAR_REGISTER_27_REG(data)                   *(short unsigned *)(CLEAR_REGISTER_27_REG               ) = data
#define IO_WR_MON_BLOCK_B_LAST_ADDR_REG(data)               *(short unsigned *)(MON_BLOCK_B_LAST_ADDR_REG           ) = data
#define IO_WR_BC_CUR_MSG_ADDR_REG(data)                     *(short unsigned *)(BC_CUR_MSG_ADDR_REG                 ) = data
#define IO_WR_CLEAR_REGISTER_28_REG(data)                   *(short unsigned *)(CLEAR_REGISTER_28_REG               ) = data
#define IO_WR_RT_LOG_PTR_TABLE_ADDR_REG(data)               *(short unsigned *)(RT_LOG_PTR_TABLE_ADDR_REG           ) = data
#define IO_WR_EXTERNAL_RTU_ADDR_BUFL_REG(data)              *(short unsigned *)(EXTERNAL_RTU_ADDR_BUFL_REG          ) = data
#define IO_WR_BC_MU_IRQ_VECTOR_REG(data)                    *(short unsigned *)(BC_MU_IRQ_VECTOR_REG                ) = data
*/

#endif

