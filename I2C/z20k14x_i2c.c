#include <stdio.h>
#include <string.h>

#include "z20k14x_i2c.h"

#define I2C_INT_32BITS 32

static I2C_initHandler_t _int_handler[I2C_DEV_NUM][I2C_INT_32BITS] = {0};

static uint32_t _interrupt_mask0 = 0x00UL;
static uint32_t _interrupt_mask1 = 0x00UL;

void I2C_intCallbackRegister(I2C_TypeDef* I2Cx,I2C_intCtrlBit_t bit,I2C_initHandler_t callback)
{
  if(I2Cx == I2C0)
  {
    _int_handler[I2C0_DEV][bit] = callback;
  }
  else if(I2Cx == I2C1)
  {
    _int_handler[I2C1_DEV][bit] = callback;
  }
  (void)_int_handler;
}

void I2C_intFlagClear(I2C_TypeDef* I2Cx,I2C_intCtrlBit_t bit)
{
  if((I2C_RX_FULL_IE != bit) && (I2C_TX_EMPTY_IE != bit))
  {
    I2C0->STATUS0 = 0x01UL << bit;
  }
}

void I2C0_IRQHandler(void)
{
  for(I2C_intCtrlBit_t bit = I2C_CALL_IE;bit <= I2C_TX_EMPTY_IE;bit++)
  {
    if(Set == I2C_intStatusGet(I2C0, bit))
    {
      _int_handler[I2C0_DEV][bit]();

      if((I2C_RX_FULL_IE != bit) && (I2C_TX_EMPTY_IE != bit))
      {
        I2C0->STATUS0 = 0x01UL << bit;
      }
    }
  }
}

void I2C1_IRQHandler(void)
{
  for(I2C_intCtrlBit_t bit = I2C_CALL_IE;bit <= I2C_TX_EMPTY_IE;bit++)
  {
    if(Set == I2C_intStatusGet(I2C1, bit))
    {
      _int_handler[I2C1_DEV][bit]();
      
      if((I2C_RX_FULL_IE != bit) && (I2C_TX_EMPTY_IE != bit))
      {
        I2C1->STATUS0 = 0x01UL << bit;
      }
    }
  }
}

void I2C0_DriverIRQHandler(void)
{
   I2C0_IRQHandler();
   __asm volatile("DSB");
}

void I2C1_DriverIRQHandler(void)
{
   I2C1_IRQHandler();
   __asm volatile("DSB");
}

bitStatus_t I2C_intStatusGet(I2C_TypeDef* I2Cx, I2C_intCtrlBit_t bit)
{
  I2C_Status0_t flag = (I2C_Status0_t)(0x01UL << bit);
  
  if((I2Cx->INT_ENABLE & flag) && (I2Cx->STATUS0 & flag))
  {
    return Set;
  }
  
  return Reset;
}

void I2C_intEnable(I2C_TypeDef* I2Cx, I2C_intCtrlBit_t bit, ctrlState_t state)
{
  if(I2Cx == I2C0)
  {
    _interrupt_mask0 |= 0x01UL << bit;
    I2Cx->INT_ENABLE = (state?(_interrupt_mask0 |= 0x01UL << bit):(_interrupt_mask0 &= ~(0x01UL << bit)));
  }
  else if(I2Cx == I2C1)
  {
    _interrupt_mask1 |= 0x01UL << bit;
    I2Cx->INT_ENABLE = (state?(_interrupt_mask1 |= 0x01UL << bit):(_interrupt_mask1 &= ~(0x01UL << bit)));
  }
}

bitStatus_t I2C_flagStatus0Get(I2C_TypeDef* I2Cx, I2C_Status0_t flagBit)
{
  return ((I2Cx->STATUS0 & flagBit)?Set:Reset);
}

bitStatus_t I2C_flagStatus1Get(I2C_TypeDef* I2Cx, I2C_Status1_t flagBit)
{
  return ((I2Cx->STATUS1 & flagBit)?Set:Reset);
}

bitStatus_t I2C_errStatusGet(I2C_TypeDef* I2Cx, I2C_errStatus_t flagBit)
{
  return ((I2Cx->ERROR_STATUS & flagBit)?Set:Reset);
}

void I2C_errorStatusAllClear(I2C_TypeDef* I2Cx)
{
  uint32_t rd_register = I2Cx->RD_CLR_ERR_STATUS;
  (void)rd_register;
}

void I2C_SDASetupTimeConfig(I2C_TypeDef* I2Cx, uint32_t setup_time_ns,uint32_t clock_MHz)
{
  uint32_t I2C_status = I2Cx->CONFIG0 & 0x01UL;
  I2Cx->CONFIG0 &= ~0x01UL;
  I2Cx->SDA_SETUP_TIMING = (uint32_t)(setup_time_ns * clock_MHz /1000 + 0x01);
  I2Cx->CONFIG0 |= I2C_status;
}

void I2C_SDAHoldTimeConfig(I2C_TypeDef* I2Cx, const I2C_holdTimeParam_t* config,uint32_t clock_MHz)
{
  uint32_t I2C_status = I2Cx->CONFIG0 & 0x01UL;
  I2Cx->CONFIG0 &= ~0x01UL;
  I2Cx->SDA_HOLD_TIMING = (config->SDA_TxHoldTime * clock_MHz / 1000) | ((config->SDA_RxHoldTime * clock_MHz / 1000) << 0x10);
  I2Cx->CONFIG0 |= I2C_status;
}

void I2C_SCLHighLowDurationConfig(I2C_TypeDef* I2Cx, const I2C_SCLDurationParam_t* config, uint32_t clock_MHz)
{
  uint32_t I2C_status = I2Cx->CONFIG0 & 0x01UL;
  uint32_t spike_count = ((I2Cx->CONFIG1 & (0x03 << 6)) == 0x03)?I2Cx->HS_SPKCNT:I2Cx->FSTD_SPKCNT;
  uint32_t low_duration = config->SCL_Low_Duration * clock_MHz / 1000 - 1;
  uint32_t high_duration = config->SCL_High_Duration * clock_MHz / 1000 - spike_count - 7;
  const uint32_t scl_high_count = 65525UL;
  
  I2Cx->CONFIG0 &= ~0x01UL;
  
  I2C_speed_t speed = (I2C_speed_t)((I2Cx->CONFIG1 >> 0x06) & 0x03);
  if(speed == I2C_Standard)
  {
    I2Cx->STD_SCL_LCNT = low_duration;
    I2Cx->STD_SCL_HCNT = ((high_duration <= scl_high_count)?high_duration:scl_high_count);
  }
  else if(speed == I2C_Fast)
  {
    I2Cx->FST_SCL_LCNT = low_duration;
    I2Cx->FST_SCL_HCNT = ((high_duration <= scl_high_count)?high_duration:scl_high_count);
  }
  else if(speed == I2C_High)
  {
    I2Cx->HS_SCL_LCNT = low_duration;
    I2Cx->HS_SCL_HCNT = ((high_duration <= scl_high_count)?high_duration:scl_high_count);
  }
  
  I2Cx->CONFIG0 |= I2C_status;
}

void I2C_spikeSuppressionLimitConfig (I2C_TypeDef* I2Cx, const I2C_SpikeLengthParam_t* config)
{
  uint32_t I2C_status = I2Cx->CONFIG0 & 0x01UL;  
  I2Cx->CONFIG0 &= ~0x01UL;
  
  I2Cx->FSTD_SPKCNT = config->fast_std_spike_cnt;
  I2Cx->HS_SPKCNT = config->high_spike_cnt;
  
  I2Cx->CONFIG0 |= I2C_status;
}

void I2C_SCLStuckLowTimeout(I2C_TypeDef* I2Cx, uint32_t timeout,uint32_t clock_MHz)             //unit:ns
{
  I2Cx->SCL_LOW_TIMEOUT = (uint32_t)(timeout * clock_MHz / 1000);
}

void I2C_SDAStuckLowTimeout(I2C_TypeDef* I2Cx, uint32_t timeout,uint32_t clock_MHz)             //unit:ns
{
  I2Cx->SDA_LOW_TIMEOUT = (uint32_t)(timeout * clock_MHz / 1000);
}

void I2C_enable(I2C_TypeDef* I2Cx,ctrlState_t state)
{
  if(state == Enable)
  {
    I2Cx->CONFIG0 |= 0x01UL;
  }
  else if(state == Disable)
  {
    I2Cx->CONFIG0 &= ~0x01UL;
  }
}

void I2C_init(I2C_TypeDef* I2Cx, const I2C_config_t* config)
{  
  uint32_t I2C_status = I2Cx->CONFIG0 & 0x01UL;  
  I2Cx->CONFIG0 &= ~0x01UL;
  
  I2Cx->CONFIG0 |= 0x01UL << 5;
  I2Cx->CONFIG1 = (config->masterSlaveMode << 0) | 0x013CUL | (config->speedMode << 6) | (config->addrBitMode << 9);
  I2Cx->SLAVE_ADDR = config->localAddr;
  I2Cx->INT_ENABLE = ((I2Cx == I2C0)?(_interrupt_mask0 = 0x00UL):(_interrupt_mask1 = 0x00UL));
    
  I2Cx->CONFIG0 |= I2C_status;
}

void I2C_FIFOLevelSet(I2C_TypeDef* I2Cx, const I2C_FIFOParam_t* config)
{
  I2Cx->RXFIFO_WATER_MARK = config->RxFIFO_Water_Mark;
  I2Cx->TXFIFO_WATER_MARK = config->TxFIFO_Water_Mark;
}

uint32_t I2C_RxFIFOCountGet(I2C_TypeDef* I2Cx)
{
  return I2Cx->RX_FIFO_CNT;
}

uint32_t I2C_TxFIFOCountGet(I2C_TypeDef* I2Cx)
{
  return I2Cx->TX_FIFO_CNT;
}

void I2C_DMAWatermarkSet(I2C_TypeDef* I2Cx, const I2C_DMAParam_t* config)
{
  I2Cx->DMA_CTRL |= (config->DMA_TXFIFO_WATERMARK << 0x02) | (config->DMA_RXFIFO_WATERMARK << 0x04);
}

void I2C_DMAEnable(I2C_TypeDef* I2Cx, ctrlState_t RxCtrl, ctrlState_t TxCtrl)
{
  I2Cx->DMA_CTRL |= RxCtrl | (TxCtrl << 0x01);
}

void I2C_targetAddressSet(I2C_TypeDef* I2Cx, uint32_t target_address,I2C_targetAddrType_t type)
{
  uint32_t I2C_status = I2Cx->CONFIG0 & 0x01UL;  
  I2Cx->CONFIG0 &= ~0x01UL;
  
  I2Cx->DEST_ADDR = ((target_address & 0x3FF) | (type << 0x0A));
  
  I2Cx->CONFIG0 |= I2C_status;
}

uint8_t I2C_receiveData(I2C_TypeDef* I2Cx)
{
  return (uint8_t)(I2Cx->COMMAND_DATA & 0xFF);
}

void I2C_transmitData(I2C_TypeDef* I2Cx, uint8_t dataByte,I2C_restartStop_t cmd)
{
  I2Cx->COMMAND_DATA = (uint32_t)(dataByte | (cmd << 9));
}

void I2C_receiveDirection(I2C_TypeDef* I2Cx,I2C_recvOpt_t opt)
{
  I2Cx->COMMAND_DATA = (((opt == ACK)?I2C_RESET_EN:I2C_STOP_EN) << 9) | (0x01UL << 8);
}

void I2C_masterACK(I2C_TypeDef* I2Cx,ctrlState_t state)
{
  I2Cx->COMMAND_DATA = (((state == Enable)?I2C_RESET_STOP_DIS:I2C_STOP_EN) << 9) | (0x01UL << 8);
}

void I2C_slaveACK(I2C_TypeDef* I2Cx,ctrlState_t state)
{
  uint32_t config = state?(I2Cx->CONFIG0 & ~(0x01 << 2)):(I2Cx->CONFIG0 | (0x01 << 2));
  
  if(I2Cx->STATUS1 & (0x01UL << 1))
  {
    I2Cx->CONFIG0 &= ~0x01UL;
    I2Cx->CONFIG0 = config;
    I2Cx->CONFIG0 |= 0x01UL;
  }
  else
  {
    I2Cx->CONFIG0 = config;
  }
}

void I2C_masterTransferAbort(I2C_TypeDef* I2Cx)
{
  I2Cx->CONFIG0 |= 0x01UL << 4;
}

uint32_t I2C_AllErrorStatusClear(I2C_TypeDef* I2Cx)
{
  return I2Cx->RD_CLR_ERR_STATUS;
}

retState_t I2C_masterBlockTxFIFO(I2C_TypeDef* I2Cx)
{
  retState_t status = FALSE;
  if(((I2Cx->STATUS1 & 0x01UL) == 0x00) && (I2Cx->TX_FIFO_CNT == 0x00))
  {
    I2Cx->CONFIG0 |= 0x01UL << 6;
    status = TRUE;
  }
  return status;
}


void I2C0_registerPrint(void)
{
  printf("\n");
  printf("I2C0_PARAMETER = 0x%x\n",I2C0_PARAMETER);
  printf("I2C0_CONFIG0 = 0x%x\n",I2C0_CONFIG0);
  printf("I2C0_CONFIG1 = 0x%x\n",I2C0_CONFIG1);
  printf("I2C0_SDA_SETUP_TIMING = 0x%x\n",I2C0_SDA_SETUP_TIMING);
  printf("I2C0_SDA_HOLD_TIMING = 0x%x\n",I2C0_SDA_HOLD_TIMING);
  printf("I2C0_DMA_CTRL = 0x%x\n",I2C0_DMA_CTRL);
  printf("I2C0_INT_ENABLE = 0x%x\n",I2C0_INT_ENABLE);
  printf("I2C0_DEST_ADDR = 0x%x\n",I2C0_DEST_ADDR);
  printf("I2C0_SLAVE_ADDR = 0x%x\n",I2C0_SLAVE_ADDR);
  printf("I2C0_STD_SCL_HCNT = 0x%x\n",I2C0_STD_SCL_HCNT);
  printf("I2C0_STD_SCL_LCNT = 0x%x\n",I2C0_STD_SCL_LCNT);
  printf("I2C0_FST_SCL_HCNT = 0x%x\n",I2C0_FST_SCL_HCNT);
  printf("I2C0_FST_SCL_LCNT = 0x%x\n",I2C0_FST_SCL_LCNT);
  printf("I2C0_HS_SCL_HCNT = 0x%x\n",I2C0_HS_SCL_HCNT);
  printf("I2C0_HS_SCL_LCNT = 0x%x\n",I2C0_HS_SCL_LCNT);
  printf("I2C0_RXFIFO_WATER_MARK = 0x%x\n",I2C0_RXFIFO_WATER_MARK);
  printf("I2C0_TXFIFO_WATER_MARK = 0x%x\n",I2C0_TXFIFO_WATER_MARK);
  printf("I2C0_TX_FIFO_CNT = 0x%x\n",I2C0_TX_FIFO_CNT);
  printf("I2C0_RX_FIFO_CNT = 0x%x\n",I2C0_RX_FIFO_CNT);
  printf("I2C0_FSTD_SPKCNT = 0x%x\n",I2C0_FSTD_SPKCNT);
  printf("I2C0_HS_SPKCNT = 0x%x\n",I2C0_HS_SPKCNT);
  printf("I2C0_STATUS0 = 0x%x\n",I2C0_STATUS0);
  printf("I2C0_STATUS1 = 0x%x\n",I2C0_STATUS1);
  printf("I2C0_ERROR_STATUS = 0x%x\n",I2C0_ERROR_STATUS);
  printf("I2C0_SCL_LOW_TIMEOUT = 0x%x\n",I2C0_SCL_LOW_TIMEOUT);
  printf("I2C0_SDA_LOW_TIMEOUT = 0x%x\n",I2C0_SDA_LOW_TIMEOUT);
  printf("\n");
}

void I2C1_registerPrint(void)
{
  printf("\n");
  printf("I2C1_PARAMETER = 0x%x\n",I2C1_PARAMETER);
  printf("I2C1_CONFIG0 = 0x%x\n",I2C1_CONFIG0);
  printf("I2C1_CONFIG1 = 0x%x\n",I2C1_CONFIG1);
  printf("I2C1_SDA_SETUP_TIMING = 0x%x\n",I2C1_SDA_SETUP_TIMING);
  printf("I2C1_SDA_HOLD_TIMING = 0x%x\n",I2C1_SDA_HOLD_TIMING);
  printf("I2C1_DMA_CTRL = 0x%x\n",I2C1_DMA_CTRL);
  printf("I2C1_INT_ENABLE = 0x%x\n",I2C1_INT_ENABLE);
  printf("I2C1_DEST_ADDR = 0x%x\n",I2C1_DEST_ADDR);
  printf("I2C1_SLAVE_ADDR = 0x%x\n",I2C1_SLAVE_ADDR);
  printf("I2C1_STD_SCL_HCNT = 0x%x\n",I2C1_STD_SCL_HCNT);
  printf("I2C1_STD_SCL_LCNT = 0x%x\n",I2C1_STD_SCL_LCNT);
  printf("I2C1_FST_SCL_HCNT = 0x%x\n",I2C1_FST_SCL_HCNT);
  printf("I2C1_FST_SCL_LCNT = 0x%x\n",I2C1_FST_SCL_LCNT);
  printf("I2C1_HS_SCL_HCNT = 0x%x\n",I2C1_HS_SCL_HCNT);
  printf("I2C1_HS_SCL_LCNT = 0x%x\n",I2C1_HS_SCL_LCNT);
  printf("I2C1_RXFIFO_WATER_MARK = 0x%x\n",I2C1_RXFIFO_WATER_MARK);
  printf("I2C1_TXFIFO_WATER_MARK = 0x%x\n",I2C1_TXFIFO_WATER_MARK);
  printf("I2C1_TX_FIFO_CNT = 0x%x\n",I2C1_TX_FIFO_CNT);
  printf("I2C1_RX_FIFO_CNT = 0x%x\n",I2C1_RX_FIFO_CNT);
  printf("I2C1_FSTD_SPKCNT = 0x%x\n",I2C1_FSTD_SPKCNT);
  printf("I2C1_HS_SPKCNT = 0x%x\n",I2C1_HS_SPKCNT);
  printf("I2C1_STATUS0 = 0x%x\n",I2C1_STATUS0);
  printf("I2C1_STATUS1 = 0x%x\n",I2C1_STATUS1);
  printf("I2C1_ERROR_STATUS = 0x%x\n",I2C1_ERROR_STATUS);
  printf("I2C1_SCL_LOW_TIMEOUT = 0x%x\n",I2C1_SCL_LOW_TIMEOUT);
  printf("I2C1_SDA_LOW_TIMEOUT = 0x%x\n",I2C1_SDA_LOW_TIMEOUT);
  printf("\n");
}

void I2C_errorPrint(I2C_TypeDef* I2Cx,char* error_dev)
{
  uint32_t error_status = I2Cx->ERROR_STATUS;
  if(error_status & (0x01UL << 0))
  {
    printf("I2C %s Error Source Bit %d is ERR_GEN_CALL_NO_ACK\n",error_dev,0);
  }
  if(error_status & (0x01UL << 1))
  {
    printf("I2C %s Error Source Bit %d is ERR_GEN_CALL_READ\n",error_dev,1);
  }
  if(error_status & (0x01UL << 2))
  {
    printf("I2C %s Error Source Bit %d is ERR_START_BYTE_ACK_DET\n",error_dev,2);
  }
  if(error_status & (0x01UL << 3))
  {
    printf("I2C %s Error Source Bit %d is ERR_SBYTE_NORSTRT\n",error_dev,3);
  }
  if(error_status & (0x01UL << 4))
  {
    printf("I2C %s Error Source Bit %d is ERR_H_NO_RSTRT\n",error_dev,4);
  }
  if(error_status & (0x01UL << 5))
  {
    printf("I2C %s Error Source Bit %d is ERR_H_MCODE_ACK_DET\n",error_dev,5);
  }
  if(error_status & (0x01UL << 6))
  {
    printf("I2C %s Error Source Bit %d is ERR_7BIT_ADDR_NO_ACK\n",error_dev,6);
  }
  if(error_status & (0x01UL << 7))
  {
    printf("I2C %s Error Source Bit %d is ERR_10BIT_ADDR1_NO_ACK\n",error_dev,7);
  }
  if(error_status & (0x01UL << 8))
  {
    printf("I2C %s Error Source Bit %d is ERR_10BIT_ADDR2_NO_ACK\n",error_dev,8);
  }
  if(error_status & (0x01UL << 9))
  {
    printf("I2C %s Error Source Bit %d is ERR_10BIT_READ_NO_RSTRT\n",error_dev,9);
  }
  if(error_status & (0x01UL << 10))
  {
    printf("I2C %s Error Source Bit %d is ERR_DATA_NO_ACK\n",error_dev,10);
  }
  if(error_status & (0x01UL << 11))
  {
    printf("I2C %s Error Source Bit %d is ERR_MASTER_ABRT\n",error_dev,11);
  }
  if(error_status & (0x01UL << 12))
  {
    printf("I2C %s Error Source Bit %d is ERR_MASTER_DIS\n",error_dev,12);
  }
  if(error_status & (0x01UL << 13))
  {
    printf("I2C %s Error Source Bit %d is ERR_SLAVE_ARBLOST\n",error_dev,13);
  }
  if(error_status & (0x01UL << 14))
  {
    printf("I2C %s Error Source Bit %d is ERR_MASTER_LOST\n",error_dev,14);
  }
  if(error_status & (0x01UL << 15))
  {
    printf("I2C %s Error Source Bit %d is ERR_SLAVE_READ_REQ\n",error_dev,15);
  }
  if(error_status & (0x01UL << 16))
  {
    printf("I2C %s Error Source Bit %d is ERR_SLAVE_FLUSH_TXFIFO\n",error_dev,16);
  }
  if(error_status & (0x01UL << 17))
  {
    printf("I2C %s Error Source Bit %d is ERR_SDA_LOW_TIMEOUT\n",error_dev,17);
  }
  if(error_status & (0x07UL << 18))
  {
    printf("I2C %s Error Source Bit %d is ERR_TXFIFO_FLUSH_CNT %ld\n",error_dev,18,(error_status & (0x07UL << 18)));
  }
}
