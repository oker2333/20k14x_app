#ifndef Z20K14X_I2C_H
#define Z20K14X_I2C_H

#include "register.h"

#define I2C_RX_FIFO_DEPTH 4
#define I2C_TX_FIFO_DEPTH 4

typedef enum
{
  Set,
  Reset
}bitStatus_t;

typedef enum
{
  ERROR,
  OK
}I2C_status_t;

typedef enum
{
  I2C0_DEV = 0x00,
  I2C1_DEV = 0x01,
  I2C_DEV_NUM = 0x02
}I2C_Dev_t;

typedef enum
{
  I2C_7BitAddr = 0x00,
  I2C_10BitAddr = 0x03
}I2C_address_t;

typedef enum
{
  I2C_Transmit_DIR = 0x00,
  I2C_Receive_DIR = 0x01
}I2C_dir_t;

typedef enum
{
  I2C_Standard = 0x01,
  I2C_Fast = 0x02,
  I2C_High = 0x03
}I2C_speed_t;

typedef enum
{
  Slave_Mode = 0x00,
  Master_Mode = 0x03,
  Master_Slave_Mode = 0x02
}I2C_mode_t;

typedef enum
{
  I2C_RESET_STOP_DIS = 0x00,
  I2C_STOP_EN = 0x01,
  I2C_RESET_EN = 0x02,
  I2C_RESET_STOP_EN = 0x03
}I2C_restartStop_t;

typedef enum{
  NACK = 0x00,
  ACK
}I2C_recvOpt_t;

typedef enum{
  Single_Target_Addr = 0x01,
  General_Call_Addr = 0x02,
  Start_Byte_Addr = 0x03
}I2C_targetAddrType_t;

typedef struct
{
  I2C_address_t addrBitMode;
  uint32_t localAddr;
  I2C_speed_t speedMode;
  I2C_mode_t masterSlaveMode;
}I2C_config_t;

typedef struct
{
  uint32_t RxFIFO_Water_Mark;
  uint32_t TxFIFO_Water_Mark;
}I2C_FIFOParam_t;

typedef struct
{
  uint32_t DMA_RXFIFO_WATERMARK;
  uint32_t DMA_TXFIFO_WATERMARK;
}I2C_DMAParam_t;

typedef struct
{
  uint16_t SDA_TxHoldTime;
  uint16_t SDA_RxHoldTime;
}I2C_holdTimeParam_t;

typedef struct
{
  uint32_t SCL_Low_Duration;
  uint32_t SCL_High_Duration;
}I2C_SCLDurationParam_t;

typedef struct
{
  uint32_t fast_std_spike_cnt;
  uint32_t high_spike_cnt;
}I2C_SpikeLengthParam_t;

typedef enum
{
  GENERAL_CALL = 0x01UL << 0,
  TXFIFO_OVERUN = 0x01UL << 1,
  ERROR_ABORT = 0x01UL << 2,
  ACTIVITY = 0x01UL << 3,
  STOP_DETECT = 0x01UL << 4,
  START_DETECT = 0x01UL << 5,
  SLAVE_READ_REQ = 0x01UL << 22,
  RXFIFO_DONE = 0x01UL << 23,
  RXFIFO_UNDERUN = 0x01UL << 24,
  RXFIFO_OVERUN = 0x01UL << 25,
  RESTART_DET = 0x01UL << 26,
  SCL_STUCK_AT_LOW = 0x01UL << 27,
  RXFIFO_FULL = 0x01UL << 30,
  TXFIFO_EMPTY = 0x01UL << 31
}I2C_Status0_t;

typedef enum
{
  MASTER_IS_ACTIVE = 0x01UL << 0,
  SLAVE_IS_ACTIVE = 0x01UL << 1,
  TXFIFO_EMPTY_MASTER_HOLD = 0x01UL << 2,
  TXFIFO_EMPTY_SLAVE_HOLD = 0x01UL << 3,
  RXFIFO_FULL_MASTER_HOLD = 0x01UL << 4,
  RXFIFO_FULL_SLAVE_HOLD = 0x01UL << 5,
  TXFIFO_IS_NOT_FULL = 0x01UL << 6,
  TXFIFO_IS_EMPTY = 0x01UL << 7,
  RXFIFO_IS_NOT_EMPTY = 0x01UL << 8,
  RXFIFO_IS_FULL = 0x01UL << 9,
  SDA_ERR_RECOVER_STUCK_LOW = 0x01UL << 10,
  SLAVE_IS_DISABLED_UNDER_ACT = 0x01UL << 11,
  SLAVE_RX_DATA_DISCARD = 0x01UL << 12,
  I2C_IS_ENABLE = 0x01UL << 13
}I2C_Status1_t;

typedef enum
{
  ERR_GEN_CALL_NO_ACK = 0x01UL << 0,
  ERR_GEN_CALL_READ = 0x01UL << 1,
  ERR_START_BYTE_ACK_DET = 0x01UL << 2,
  ERR_SBYTE_NORSTRT = 0x01UL << 3,
  ERR_H_NO_RSTRT = 0x01UL << 4,
  ERR_H_MCODE_ACK_DET = 0x01UL << 5,
  ERR_7BIT_ADDR_NO_ACK = 0x01UL << 6,
  ERR_10BIT_ADDR1_NO_ACK = 0x01UL << 7,
  ERR_10BIT_ADDR2_NO_ACK = 0x01UL << 8,
  ERR_10BIT_READ_NO_RSTRT = 0x01UL << 9,
  ERR_DATA_NO_ACK = 0x01UL << 10,
  ERR_MASTER_ABRT = 0x01UL << 11,
  ERR_MASTER_DIS = 0x01UL << 12,
  ERR_SLAVE_ARBLOST = 0x01UL << 13,
  ERR_MASTER_LOST = 0x01UL << 14,
  ERR_SLAVE_READ_REQ = 0x01UL << 15,
  ERR_SLAVE_FLUSH_TXFIFO = 0x01UL << 16,
  ERR_SDA_LOW_TIMEOUT = 0x01UL << 17,
  ERR_TXFIFO_FLUSH_CNT = 0x01UL << 18
}I2C_errStatus_t;

typedef enum
{
  I2C_CALL_IE = 0,
  I2C_TX_OVF_IE = 1,
  I2C_ERROR_ABORT_IE = 2,
  I2C_ACTIVITY_DET_IE = 3,
  I2C_STOP_DET_IE = 4,
  I2C_START_DET_IE = 5,
  I2C_SLAVE_RD_REQ_IE = 22,
  I2C_RX_DONE_IE = 23,
  I2C_RX_UNDER_IE = 24,
  I2C_RX_OVF_IE = 25,
  I2C_RESTART_DET_IE = 26,
  I2C_SCL_STUCK_AT_LOW_IE =27,
  I2C_RX_FULL_IE = 30,
  I2C_TX_EMPTY_IE = 31
}I2C_intCtrlBit_t;

typedef void (*I2C_initHandler_t)(void);

void I2C_intEnable(I2C_TypeDef* I2Cx, I2C_intCtrlBit_t bit, ctrlState_t state);

void I2C_intCallbackRegister(I2C_TypeDef* I2Cx,I2C_intCtrlBit_t bit,I2C_initHandler_t callback);

void I2C_intFlagClear(I2C_TypeDef* I2Cx,I2C_intCtrlBit_t bit);

bitStatus_t I2C_intStatusGet(I2C_TypeDef* I2Cx, I2C_intCtrlBit_t flagBit);

bitStatus_t I2C_flagStatus0Get(I2C_TypeDef* I2Cx, I2C_Status0_t flagBit);

bitStatus_t I2C_flagStatus1Get(I2C_TypeDef* I2Cx, I2C_Status1_t flagBit);

bitStatus_t I2C_errStatusGet(I2C_TypeDef* I2Cx, I2C_errStatus_t flagBit);

void I2C_errorStatusAllClear(I2C_TypeDef* I2Cx);

void I2C_SDASetupTimeConfig(I2C_TypeDef* I2Cx, uint32_t setup_time_ns,uint32_t clock_MHz);

void I2C_SDAHoldTimeConfig(I2C_TypeDef* I2Cx, const I2C_holdTimeParam_t* config,uint32_t clock_MHz);

void I2C_SCLHighLowDurationConfig(I2C_TypeDef* I2Cx, const I2C_SCLDurationParam_t* config, uint32_t clock_MHz);

void I2C_spikeSuppressionLimitConfig (I2C_TypeDef* I2Cx, const I2C_SpikeLengthParam_t* config);

void I2C_SCLStuckLowTimeout(I2C_TypeDef* I2Cx, uint32_t timeout,uint32_t clock_MHz);

void I2C_SDAStuckLowTimeout(I2C_TypeDef* I2Cx, uint32_t timeout,uint32_t clock_MHz);

void I2C_enable(I2C_TypeDef* I2Cx,ctrlState_t state);

void I2C_init(I2C_TypeDef* I2Cx, const I2C_config_t* config);

void I2C_FIFOLevelSet(I2C_TypeDef* I2Cx, const I2C_FIFOParam_t* config);

void I2C_DMAWatermarkSet(I2C_TypeDef* I2Cx, const I2C_DMAParam_t* config);

void I2C_DMAEnable(I2C_TypeDef* I2Cx, ctrlState_t RxCtrl, ctrlState_t TxCtrl);

uint32_t I2C_RxFIFOCountGet(I2C_TypeDef* I2Cx);

uint32_t I2C_TxFIFOCountGet(I2C_TypeDef* I2Cx);

void I2C_targetAddressSet(I2C_TypeDef* I2Cx, uint32_t target_address,I2C_targetAddrType_t type);

void I2C_transmitData(I2C_TypeDef* I2Cx, uint8_t dataByte,I2C_restartStop_t cmd);

uint8_t I2C_receiveData(I2C_TypeDef* I2Cx);

void I2C_receiveDirection(I2C_TypeDef* I2Cx,I2C_recvOpt_t opt);

void I2C_masterACK(I2C_TypeDef* I2Cx,ctrlState_t state);

void I2C_slaveACK(I2C_TypeDef* I2Cx,ctrlState_t state);

void I2C_masterTransferAbort(I2C_TypeDef* I2Cx);

uint32_t I2C_AllErrorStatusClear(I2C_TypeDef* I2Cx);

retState_t I2C_masterBlockTxFIFO(I2C_TypeDef* I2Cx);

void I2C0_registerPrint(void);

void I2C1_registerPrint(void);

void I2C_errorPrint(I2C_TypeDef* I2Cx,char* error_dev);

#ifndef IIC_REGISTERS

#define I2C0_PARAMETER *((volatile unsigned int*)(I2C0_BASE_ADDRESS + 0x04))
#define I2C0_CONFIG0 *((volatile unsigned int*)(I2C0_BASE_ADDRESS + 0x08))
#define I2C0_CONFIG1 *((volatile unsigned int*)(I2C0_BASE_ADDRESS + 0x0C))
#define I2C0_SDA_SETUP_TIMING *((volatile unsigned int*)(I2C0_BASE_ADDRESS + 0x10))
#define I2C0_SDA_HOLD_TIMING *((volatile unsigned int*)(I2C0_BASE_ADDRESS + 0x14))
#define I2C0_DMA_CTRL *((volatile unsigned int*)(I2C0_BASE_ADDRESS + 0x18))
#define I2C0_INT_ENABLE *((volatile unsigned int*)(I2C0_BASE_ADDRESS + 0x1C))
#define I2C0_COMMAND_DATA *((volatile unsigned int*)(I2C0_BASE_ADDRESS + 0x20))
#define I2C0_DEST_ADDR *((volatile unsigned int*)(I2C0_BASE_ADDRESS + 0x24))
#define I2C0_SLAVE_ADDR *((volatile unsigned int*)(I2C0_BASE_ADDRESS + 0x28))
#define I2C0_STD_SCL_HCNT *((volatile unsigned int*)(I2C0_BASE_ADDRESS + 0x2C))
#define I2C0_STD_SCL_LCNT *((volatile unsigned int*)(I2C0_BASE_ADDRESS + 0x30))
#define I2C0_FST_SCL_HCNT *((volatile unsigned int*)(I2C0_BASE_ADDRESS + 0x34))
#define I2C0_FST_SCL_LCNT *((volatile unsigned int*)(I2C0_BASE_ADDRESS + 0x38))
#define I2C0_HS_SCL_HCNT *((volatile unsigned int*)(I2C0_BASE_ADDRESS + 0x3C))
#define I2C0_HS_SCL_LCNT *((volatile unsigned int*)(I2C0_BASE_ADDRESS + 0x40))
#define I2C0_RXFIFO_WATER_MARK *((volatile unsigned int*)(I2C0_BASE_ADDRESS + 0x44))
#define I2C0_TXFIFO_WATER_MARK *((volatile unsigned int*)(I2C0_BASE_ADDRESS + 0x48))
#define I2C0_TX_FIFO_CNT *((volatile unsigned int*)(I2C0_BASE_ADDRESS + 0x4C))
#define I2C0_RX_FIFO_CNT *((volatile unsigned int*)(I2C0_BASE_ADDRESS + 0x50))
#define I2C0_FSTD_SPKCNT *((volatile unsigned int*)(I2C0_BASE_ADDRESS + 0x54))
#define I2C0_HS_SPKCNT *((volatile unsigned int*)(I2C0_BASE_ADDRESS + 0x58))
#define I2C0_STATUS0 *((volatile unsigned int*)(I2C0_BASE_ADDRESS + 0x5C))
#define I2C0_STATUS1 *((volatile unsigned int*)(I2C0_BASE_ADDRESS + 0x60))
#define I2C0_ERROR_STATUS *((volatile unsigned int*)(I2C0_BASE_ADDRESS + 0x64))
#define I2C0_SCL_LOW_TIMEOUT *((volatile unsigned int*)(I2C0_BASE_ADDRESS + 0x68))
#define I2C0_SDA_LOW_TIMEOUT *((volatile unsigned int*)(I2C0_BASE_ADDRESS + 0x6C))
#define I2C0_RD_CLR_ERR_STATUS *((volatile unsigned int*)(I2C0_BASE_ADDRESS + 0x70))

#define I2C1_PARAMETER *((volatile unsigned int*)(I2C1_BASE_ADDRESS + 0x04))
#define I2C1_CONFIG0 *((volatile unsigned int*)(I2C1_BASE_ADDRESS + 0x08))
#define I2C1_CONFIG1 *((volatile unsigned int*)(I2C1_BASE_ADDRESS + 0x0C))
#define I2C1_SDA_SETUP_TIMING *((volatile unsigned int*)(I2C1_BASE_ADDRESS + 0x10))
#define I2C1_SDA_HOLD_TIMING *((volatile unsigned int*)(I2C1_BASE_ADDRESS + 0x14))
#define I2C1_DMA_CTRL *((volatile unsigned int*)(I2C1_BASE_ADDRESS + 0x18))
#define I2C1_INT_ENABLE *((volatile unsigned int*)(I2C1_BASE_ADDRESS + 0x1C))
#define I2C1_COMMAND_DATA *((volatile unsigned int*)(I2C1_BASE_ADDRESS + 0x20))
#define I2C1_DEST_ADDR *((volatile unsigned int*)(I2C1_BASE_ADDRESS + 0x24))
#define I2C1_SLAVE_ADDR *((volatile unsigned int*)(I2C1_BASE_ADDRESS + 0x28))
#define I2C1_STD_SCL_HCNT *((volatile unsigned int*)(I2C1_BASE_ADDRESS + 0x2C))
#define I2C1_STD_SCL_LCNT *((volatile unsigned int*)(I2C1_BASE_ADDRESS + 0x30))
#define I2C1_FST_SCL_HCNT *((volatile unsigned int*)(I2C1_BASE_ADDRESS + 0x34))
#define I2C1_FST_SCL_LCNT *((volatile unsigned int*)(I2C1_BASE_ADDRESS + 0x38))
#define I2C1_HS_SCL_HCNT *((volatile unsigned int*)(I2C1_BASE_ADDRESS + 0x3C))
#define I2C1_HS_SCL_LCNT *((volatile unsigned int*)(I2C1_BASE_ADDRESS + 0x40))
#define I2C1_RXFIFO_WATER_MARK *((volatile unsigned int*)(I2C1_BASE_ADDRESS + 0x44))
#define I2C1_TXFIFO_WATER_MARK *((volatile unsigned int*)(I2C1_BASE_ADDRESS + 0x48))
#define I2C1_TX_FIFO_CNT *((volatile unsigned int*)(I2C1_BASE_ADDRESS + 0x4C))
#define I2C1_RX_FIFO_CNT *((volatile unsigned int*)(I2C1_BASE_ADDRESS + 0x50))
#define I2C1_FSTD_SPKCNT *((volatile unsigned int*)(I2C1_BASE_ADDRESS + 0x54))
#define I2C1_HS_SPKCNT *((volatile unsigned int*)(I2C1_BASE_ADDRESS + 0x58))
#define I2C1_STATUS0 *((volatile unsigned int*)(I2C1_BASE_ADDRESS + 0x5C))
#define I2C1_STATUS1 *((volatile unsigned int*)(I2C1_BASE_ADDRESS + 0x60))
#define I2C1_ERROR_STATUS *((volatile unsigned int*)(I2C1_BASE_ADDRESS + 0x64))
#define I2C1_SCL_LOW_TIMEOUT *((volatile unsigned int*)(I2C1_BASE_ADDRESS + 0x68))
#define I2C1_SDA_LOW_TIMEOUT *((volatile unsigned int*)(I2C1_BASE_ADDRESS + 0x6C))
#define I2C1_RD_CLR_ERR_STATUS *((volatile unsigned int*)(I2C1_BASE_ADDRESS + 0x70))

#endif

#endif
