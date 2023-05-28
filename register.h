#ifndef REGISTER_H
#define REGISTER_H

#include <stdint.h>

#define __O     volatile             /*!< Defines 'write only' permissions                */
#define __IO    volatile             /*!< Defines 'read / write' permissions              */
#define __I     volatile             /*!< Defines 'read only' permissions              */

typedef enum{
  Disable,
  Enable
}ctrlState_t;

typedef enum{
  TRUE,
  FALSE
}retState_t;

typedef volatile struct
{
  __IO uint32_t PADDING_BYTES;
  __IO uint32_t PARAMETER;
  __IO uint32_t CONFIG0;
  __IO uint32_t CONFIG1;
  __IO uint32_t SDA_SETUP_TIMING;
  __IO uint32_t SDA_HOLD_TIMING;
  __IO uint32_t DMA_CTRL;
  __IO uint32_t INT_ENABLE;
  __IO uint32_t COMMAND_DATA;
  __IO uint32_t DEST_ADDR;
  __IO uint32_t SLAVE_ADDR;
  __IO uint32_t STD_SCL_HCNT;
  __IO uint32_t STD_SCL_LCNT;
  __IO uint32_t FST_SCL_HCNT;
  __IO uint32_t FST_SCL_LCNT;
  __IO uint32_t HS_SCL_HCNT;
  __IO uint32_t HS_SCL_LCNT;
  __IO uint32_t RXFIFO_WATER_MARK;
  __IO uint32_t TXFIFO_WATER_MARK;
  __IO uint32_t TX_FIFO_CNT;
  __IO uint32_t RX_FIFO_CNT;
  __IO uint32_t FSTD_SPKCNT;
  __IO uint32_t HS_SPKCNT;
  __IO uint32_t STATUS0;
  __IO uint32_t STATUS1;
  __IO uint32_t ERROR_STATUS;
  __IO uint32_t SCL_LOW_TIMEOUT;
  __IO uint32_t SDA_LOW_TIMEOUT;
  __IO uint32_t RD_CLR_ERR_STATUS;
} I2C_TypeDef;

typedef volatile struct {
    /* 0x00*/
    uint32_t zResverd0x00;
    /* 0x04*/
    struct {
           uint32_t I2C_SUPPORT_SPEED       : 2;  /* [1:0]          ro         */
           uint32_t DMA_SUPPORT             : 1;  /* [2]            ro         */
           uint32_t TXFIFO_DEPTH            : 4;  /* [6:3]          ro         */
           uint32_t RXFIFO_DEPTH            : 4;  /* [10:7]         ro         */
           uint32_t RSVD_31_11              :21;  /* [31:11]        ro         */
    } I2C_PARAMETER;

    /* 0x08*/
    struct {
           uint32_t MODULE_EN               : 1;  /* [0]            r/w        */
           uint32_t SLAVE_ACK_GENCALL       : 1;  /* [1]            r/w        */
           uint32_t SLAVE_NACK              : 1;  /* [2]            r/w        */
           uint32_t SDA_RECOVER_EN          : 1;  /* [3]            r/w        */
           uint32_t MASTER_ABORT            : 1;  /* [4]            r/w        */
           uint32_t MASTER_BUS_RECOVER_EN   : 1;  /* [5]            r/w        */
           uint32_t MASTER_BLK_TXFIFO       : 1;  /* [6]            r/w        */
           uint32_t H_MCODE                 : 3;  /* [9:7]          r/w        */
           uint32_t RSVD_31_10              :22;  /* [31:10]        ro         */
    } I2C_CONFIG0;

    /* 0x0c*/
    struct {
           uint32_t SLAVE_MODE_DIS          : 1;  /* [0]            r/w        */
           uint32_t MASTER_MODE_EN          : 1;  /* [1]            r/w        */
           uint32_t MASTER_RESTART_EN       : 1;  /* [2]            r/w        */
           uint32_t SLAVE_STOP_DET_EN       : 1;  /* [3]            r/w        */
           uint32_t MASTER_STOP_DET_EN      : 1;  /* [4]            r/w        */
           uint32_t TXFIFO_EMPTY_EN         : 1;  /* [5]            r/w        */
           uint32_t SPEED_SEL               : 2;  /* [7:6]          r/w        */
           uint32_t HOLD_EN_RXFIFO_FULL     : 1;  /* [8]            r/w        */
           uint32_t SLAVE_10BIT_ADDR_SEL    : 1;  /* [9]            r/w        */
           uint32_t MASTER_10BIT_ADDR_SEL   : 1;  /* [10]           r/w        */
           uint32_t RSVD_31_11              :21;  /* [31:11]        ro         */
    } I2C_CONFIG1;

    /* 0x10*/
    struct {
           uint32_t SDA_SETUP_TIMING        : 8;  /* [7:0]          r/w        */
           uint32_t RSVD_31_8               :24;  /* [31:8]         ro         */
    } I2C_SDA_SETUP_TIMING;

    /* 0x14*/
    struct {
           uint32_t SDA_TX_HOLD_TIMING      :16;  /* [15:0]         r/w        */
           uint32_t SDA_RX_HOLD_TIMING      : 8;  /* [23:16]        r/w        */
           uint32_t RSVD_31_24              : 8;  /* [31:24]        ro         */
    } I2C_SDA_HOLD_TIMING;

    /* 0x18*/
    struct {
           uint32_t RXFIFO_DMA_EN           : 1;  /* [0]            r/w        */
           uint32_t TXFIFO_DMA_EN           : 1;  /* [1]            r/w        */
           uint32_t DMA_TXFIFO_WATERMARK    : 2;  /* [3:2]          r/w        */
           uint32_t DMA_RXFIFO_WATERMARK    : 2;  /* [5:4]          r/w        */
           uint32_t RSVD_31_6               :26;  /* [31:6]         ro         */
    } I2C_DMA_CTRL;

    /* 0x1c*/
    struct {
           uint32_t I2C_CALL_IE             : 1;  /* [0]            r/w        */
           uint32_t I2C_TX_OVF_IE           : 1;  /* [1]            r/w        */
           uint32_t I2C_ERROR_ABORT_IE      : 1;  /* [2]            r/w        */
           uint32_t I2C_ACTIVITY_DET_IE     : 1;  /* [3]            r/w        */
           uint32_t I2C_STOP_DET_IE         : 1;  /* [4]            r/w        */
           uint32_t I2C_START_DET_IE        : 1;  /* [5]            r/w        */
           uint32_t RSVD_21_6               :16;  /* [21:6]         ro         */
           uint32_t SLAVE_RD_REQ_IE         : 1;  /* [22]           r/w        */
           uint32_t RX_DONE_IE              : 1;  /* [23]           r/w        */
           uint32_t RX_UNDER_IE             : 1;  /* [24]           r/w        */
           uint32_t RX_OVF_IE               : 1;  /* [25]           r/w        */
           uint32_t RESTART_DET_IE          : 1;  /* [26]           r/w        */
           uint32_t SCL_STUCK_AT_LOW_IE     : 1;  /* [27]           r/w        */
           uint32_t RSVD_29_28              : 2;  /* [29:28]        ro         */
           uint32_t RX_FULL_IE              : 1;  /* [30]           r/w        */
           uint32_t TX_EMPTY_IE             : 1;  /* [31]           r/w        */
    } I2C_INT_ENABLE;

    /* 0x20*/
    struct {
           uint32_t DATA                    : 8;  /* [7:0]          r/w        */
           uint32_t CMD_MASTER_DIRECTION    : 1;  /* [8]            wo         */
           uint32_t CMD_STOP                : 1;  /* [9]            wo         */
           uint32_t CMD_RESTART             : 1;  /* [10]           wo         */
           uint32_t RSVD_31_11              :21;  /* [31:11]        ro         */
    } I2C_COMMAND_DATA;

    /* 0x24*/
    struct {
           uint32_t DEST_ADDR               :10;  /* [9:0]          r/w        */
           uint32_t MASTER_CMD_SEL          : 2;  /* [11:10]        r/w        */
           uint32_t RSVD_31_12              :20;  /* [31:12]        ro         */
    } I2C_DEST_ADDR;

    /* 0x28*/
    struct {
           uint32_t SLV_ADDR                :10;  /* [9:0]          r/w        */
           uint32_t RSVD_31_10              :22;  /* [31:10]        ro         */
    } I2C_SLAVE_ADDR;

    /* 0x2c*/
    struct {
           uint32_t STD_SCL_HCNT            :16;  /* [15:0]         r/w        */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } I2C_STD_SCL_HCNT;

    /* 0x30*/
    struct {
           uint32_t STD_SCL_LCNT            :16;  /* [15:0]         r/w        */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } I2C_STD_SCL_LCNT;

    /* 0x34*/
    struct {
           uint32_t FST_SCL_HCNT            :16;  /* [15:0]         r/w        */
           uint32_t RSVD_31_16              :16;  /* [31:16]        reserve    */
    } I2C_FST_SCL_HCNT;

    /* 0x38*/
    struct {
           uint32_t FST_SCL_LCNT            :16;  /* [15:0]         r/w        */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } I2C_FST_SCL_LCNT;

    /* 0x3c*/
    struct {
           uint32_t HS_SCL_HCNT             :16;  /* [15:0]         r/w        */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } I2C_HS_SCL_HCNT;

    /* 0x40*/
    struct {
           uint32_t HS_SCL_LCNT             :16;  /* [15:0]         r/w        */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } I2C_HS_SCL_LCNT;

    /* 0x44*/
    struct {
           uint32_t RXFIFO_WATER_MARK       : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_31_2               :30;  /* [31:2]         ro         */
    } I2C_RXFIFO_WATER_MARK;

    /* 0x48*/
    struct {
           uint32_t TXFIFO_WATER_MARK       : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_31_2               :30;  /* [31:2]         ro         */
    } I2C_TXFIFO_WATER_MARK;

    /* 0x4c*/
    struct {
           uint32_t TX_FIFO_CNT             : 3;  /* [2:0]          ro         */
           uint32_t RSVD_31_3               :29;  /* [31:3]         ro         */
    } I2C_TX_FIFO_CNT;

    /* 0x50*/
    struct {
           uint32_t RX_FIFO_CNT             : 3;  /* [2:0]          ro         */
           uint32_t RSVD_31_3               :29;  /* [31:3]         ro         */
    } I2C_RX_FIFO_CNT;

    /* 0x54*/
    struct {
           uint32_t FSTD_SPKLEN             : 8;  /* [7:0]          r/w        */
           uint32_t RSVD_31_8               :24;  /* [31:8]         ro         */
    } I2C_FSTD_SPKCNT;

    /* 0x58*/
    struct {
           uint32_t HS_SPKLEN               : 8;  /* [7:0]          r/w        */
           uint32_t RSVD_31_8               :24;  /* [31:8]         ro         */
    } I2C_HS_SPKCNT;

    /* 0x5c*/
    struct {
           uint32_t GENERAL_CALL            : 1;  /* [0]            w1c        */
           uint32_t TXFIFO_OVERUN           : 1;  /* [1]            w1c        */
           uint32_t ERROR_ABORT             : 1;  /* [2]            w1c        */
           uint32_t ACTIVITY                : 1;  /* [3]            w1c        */
           uint32_t STOP_DETECT             : 1;  /* [4]            w1c        */
           uint32_t START_DETECT            : 1;  /* [5]            w1c        */
           uint32_t RSVD_21_6               :16;  /* [21:6]         ro         */
           uint32_t SLAVE_READ_REQ          : 1;  /* [22]           w1c        */
           uint32_t RXFIFO_DONE             : 1;  /* [23]           w1c        */
           uint32_t RXFIFO_UNDERUN          : 1;  /* [24]           w1c        */
           uint32_t RXFIFO_OVERUN           : 1;  /* [25]           w1c        */
           uint32_t RESTART_DET             : 1;  /* [26]           w1c        */
           uint32_t SCL_STUCK_AT_LOW        : 1;  /* [27]           w1c        */
           uint32_t RSVD_29_28              : 2;  /* [29:28]        ro         */
           uint32_t RXFIFO_FULL             : 1;  /* [30]           ro         */
           uint32_t TXFIFO_EMPTY            : 1;  /* [31]           ro         */
    } I2C_STATUS0;

    /* 0x60*/
    struct {
           uint32_t MASTER_IS_ACTIVE        : 1;  /* [0]            ro         */
           uint32_t SLAVE_IS_ACTIVE         : 1;  /* [1]            ro         */
           uint32_t TXFIFO_EMPTY_MASTER_HOLD: 1;  /* [2]            ro         */
           uint32_t TXFIFO_EMPTY_SLAVE_HOLD : 1;  /* [3]            ro         */
           uint32_t RXFIFO_FULL_MASTER_HOLD : 1;  /* [4]            ro         */
           uint32_t RXFIFO_FULL_SLAVE_HOLD  : 1;  /* [5]            ro         */
           uint32_t TXFIO_IS_NOT_FULL       : 1;  /* [6]            ro         */
           uint32_t TXFIFO_IS_EMPTY         : 1;  /* [7]            ro         */
           uint32_t RXFIFO_IS_NOT_EMPTY     : 1;  /* [8]            ro         */
           uint32_t RXFIO_IS_FULL           : 1;  /* [9]            ro         */
           uint32_t SDA_ERR_RECOVER_STUCK_LOW: 1;  /* [10]           ro         */
           uint32_t SLAVE_IS_DISABLED_UNDER_ACT: 1;  /* [11]           ro         */
           uint32_t SLAVE_RX_DATA_DISCARD   : 1;  /* [12]           ro         */
           uint32_t I2C_IS_ENABLE           : 1;  /* [13]           ro         */
           uint32_t RSVD_31_14              :18;  /* [31:14]        ro         */
    } I2C_STATUS1;

    /* 0x64*/
    struct {
           uint32_t ERR_GEN_CALL_NO_ACK     : 1;  /* [0]            ro         */
           uint32_t ERR_GEN_CALL_READ       : 1;  /* [1]            ro         */
           uint32_t ERR_START_BYTE_ACK_DET  : 1;  /* [2]            ro         */
           uint32_t ERR_SBYTE_NORSTRT       : 1;  /* [3]            ro         */
           uint32_t ERR_H_NO_RSTRT          : 1;  /* [4]            ro         */
           uint32_t ERR_H_MCODE_ACK_DET     : 1;  /* [5]            ro         */
           uint32_t ERR_7BIT_ADDR_NO_ACK    : 1;  /* [6]            ro         */
           uint32_t ERR_10BIT_ADDR1_NO_ACK  : 1;  /* [7]            ro         */
           uint32_t ERR_10BIT_ADDR2_NO_ACK  : 1;  /* [8]            ro         */
           uint32_t ERR_10BIT_READ_NO_RSTRT : 1;  /* [9]            ro         */
           uint32_t ERR_DATA_NO_ACK         : 1;  /* [10]           ro         */
           uint32_t ERR_MASTER_ABRT         : 1;  /* [11]           ro         */
           uint32_t ERR_MASTER_DIS          : 1;  /* [12]           ro         */
           uint32_t ERR_SLAVE_ARBLOST       : 1;  /* [13]           ro         */
           uint32_t ERR_MASTER_LOST         : 1;  /* [14]           ro         */
           uint32_t ERR_SLAVE_READ_REQ      : 1;  /* [15]           ro         */
           uint32_t ERR_SLAVE_FLUSH_TXFIFO  : 1;  /* [16]           ro         */
           uint32_t ERR_SDA_LOW_TIMEOUT     : 1;  /* [17]           ro         */
           uint32_t ERR_TXFIFO_FLUSH_CNT    : 3;  /* [20:18]        ro         */
           uint32_t RSVD_31_21              :11;  /* [31:21]        ro         */
    } I2C_ERROR_STATUS;

    /* 0x68*/
    struct {
           uint32_t SCL_LOW_TIMEOUT         :32;  /* [31:0]         r/w        */
    } I2C_SCL_LOW_TIMEOUT;

    /* 0x6c*/
    struct {
           uint32_t SDA_LOW_TIMEOUT         :32;  /* [31:0]         r/w        */
    } I2C_SDA_LOW_TIMEOUT;

    /* 0x70*/
    struct {
           uint32_t CLR_ERR                 : 1;  /* [0]            ro         */
           uint32_t RSVD_31_1               :31;  /* [31:1]         ro         */
    } I2C_RD_CLR_ERR_STATUS;

}I2C_Reg_t;

#define PERIPH_BASE     ((uint32_t)0x40000000) /*!< Peripheral base address in the alias region                                */

#define I2C0_BASE_ADDRESS       (PERIPH_BASE + 0x66000)
#define I2C1_BASE_ADDRESS       (PERIPH_BASE + 0x58000)

#define I2C0    ((I2C_TypeDef *) I2C0_BASE_ADDRESS)
#define I2C1    ((I2C_TypeDef *) I2C1_BASE_ADDRESS)

#define I2C0_base_addr    ((I2C_Reg_t *) I2C0_BASE_ADDRESS)
#define I2C1_base_addr    ((I2C_Reg_t *) I2C1_BASE_ADDRESS)

#endif

