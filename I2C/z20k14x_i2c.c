#include <stdio.h>

#include "z20k14x_i2c.h"

#define I2C_INT_32BITS 32

static I2C_initHandler_t _int_handler[I2C_DEV_NUM][I2C_INT_32BITS] = {0};

void I2C_intHandlerRegister(I2C_TypeDef* I2Cx,I2C_intCtrlBit_t bit,I2C_initHandler_t callback)
{
  if(I2Cx == I2C0)
  {
    _int_handler[I2C0_DEV][bit] = callback;
    (void)_int_handler;
  }
  else if(I2Cx == I2C1)
  {
    _int_handler[I2C1_DEV][bit] = callback;
    (void)_int_handler;
  }
}

void I2C0_IRQHandler(void)
{
  for(I2C_intCtrlBit_t bit = I2C_CALL_IE;bit <= TX_EMPTY_IE;bit++)
  {
    if(Set == I2C_intStatusGet(I2C0, bit))
    {
      _int_handler[I2C0_DEV][bit]();
      
      if((RX_FULL_IE != bit) && (TX_EMPTY_IE != bit))
      {
        I2C0->STATUS0 = 0x01UL << bit;
      }
    }
  }
}

void I2C1_IRQHandler(void)
{
  for(I2C_intCtrlBit_t bit = I2C_CALL_IE;bit <= TX_EMPTY_IE;bit++)
  {
    if(Set == I2C_intStatusGet(I2C1, bit))
    {
      _int_handler[I2C1_DEV][bit]();
      
      if((RX_FULL_IE != bit) && (TX_EMPTY_IE != bit))
      {
        I2C1->STATUS0 = 0x01UL << bit;
      }
    }
  }
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
  if(Enable)
  {
    I2Cx->INT_ENABLE |= 0x01UL << bit;
  }
  else
  {
    I2Cx->INT_ENABLE &= ~(0x01UL << bit);
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
  I2Cx->SDA_HOLD_TIMING = ((uint8_t)(config->SDA_TxHoldTime * clock_MHz / 1000)) | (((uint8_t)(config->SDA_RxHoldTime * clock_MHz / 1000)) << 0x08);
  I2Cx->CONFIG0 |= I2C_status;
}

void I2C_SCLHighLowDurationConfig(I2C_TypeDef* I2Cx, const I2C_SCLDurationParam_t* config, uint32_t clock_MHz)
{
  uint32_t I2C_status = I2Cx->CONFIG0 & 0x01UL;
  uint32_t low_duration = config->SCL_Low_Duration * clock_MHz / 1000;
  uint32_t high_duration = config->SCL_High_Duration * clock_MHz / 1000;
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

void I2C_SCLStuckLowTimeout(I2C_TypeDef* I2Cx, uint32_t timeout_ns,uint32_t clock_MHz)
{
  I2Cx->SCL_LOW_TIMEOUT = (uint32_t)(timeout_ns * clock_MHz / 1000);
}

void I2C_SDAStuckLowTimeout(I2C_TypeDef* I2Cx, uint32_t timeout_ns,uint32_t clock_MHz)
{
  I2Cx->SDA_LOW_TIMEOUT = (uint32_t)(timeout_ns * clock_MHz / 1000);
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
  I2Cx->CONFIG1 = config->masterSlaveMode | (config->restart << 0x02) | (config->speedMode << 0x06) | (config->addrBitMode << 0x09);
  I2Cx->SLAVE_ADDR = config->localAddr;
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

void I2C_transmitCmd(I2C_TypeDef* I2Cx, I2C_destType_t destType, uint16_t address, uint8_t dataByte, I2C_restartStop_t cmd)
{
  I2Cx->CONFIG0 &= ~0x01UL;
  I2Cx->DEST_ADDR = ((address & 0x3FF) | (destType << 0x0A));
  I2Cx->CONFIG0 |= 0x01UL;
  
  I2Cx->COMMAND_DATA = (uint32_t)(dataByte | (cmd << 9));
}

void I2C_receiveCmd(I2C_TypeDef* I2Cx, uint16_t address, I2C_restartStop_t cmd)
{
  I2Cx->CONFIG0 &= ~0x01UL;
  I2Cx->DEST_ADDR = ((address & 0x3FF) | (0x00UL << 0x0A));
  I2Cx->CONFIG0 |= 0x01UL;
  
  I2Cx->COMMAND_DATA = (uint32_t)(0x00UL | (cmd << 9) | (0x01UL << 8));
}

uint8_t I2C_receiveData(I2C_TypeDef* I2Cx)
{
  return (uint8_t)(I2Cx->COMMAND_DATA & 0xFF);
}

void I2C_transmitData(I2C_TypeDef* I2Cx, uint8_t dataByte,I2C_restartStop_t cmd)
{
  I2Cx->COMMAND_DATA = (uint32_t)(dataByte | (cmd << 9));
}
