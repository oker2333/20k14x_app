#include <stdio.h>

#include "z20k14x_i2c.h"

#define CALLBACK_ARRAY_ZISE 32

static I2C_initHandler_t i2c0_int_handler[CALLBACK_ARRAY_ZISE] = {0};
static I2C_initHandler_t i2c1_int_handler[CALLBACK_ARRAY_ZISE] = {0};

void I2C_intHandlerRegister(I2C_TypeDef* I2Cx,I2C_intCtrlBit_t bit,I2C_initHandler_t callback)
{
  if(I2Cx == I2C0)
  {
    i2c0_int_handler[bit] = callback;
    (void)i2c0_int_handler;
  }
  else if(I2Cx == I2C1)
  {
    i2c1_int_handler[bit] = callback;
    (void)i2c1_int_handler;
  }

}

void I2C0_IRQHandler(void)
{
  for(I2C_intCtrlBit_t bit = I2C_CALL_IE;bit <= TX_EMPTY_IE;bit++)
  {
    if(Set == I2C_intStatusGet(I2C0, bit))
    {
      i2c0_int_handler[bit]();
      I2C0->STATUS0 = 0x01UL << bit;
    }
  }
}

void I2C1_IRQHandler(void)
{
  for(I2C_intCtrlBit_t bit = I2C_CALL_IE;bit <= TX_EMPTY_IE;bit++)
  {
    if(Set == I2C_intStatusGet(I2C1, bit))
    {
      i2c1_int_handler[bit]();
      I2C1->STATUS0 = 0x01UL << bit;
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

void I2C_enable(I2C_TypeDef* I2Cx,ctrlState_t state)
{
  if(state == Enable)
  {
    I2Cx->CONFIG0 |= 0x01UL;
  }
  else if(state == Disbale)
  {
    I2Cx->CONFIG0 &= ~0x01UL;
  }
}

void I2C_init(I2C_TypeDef* I2Cx, I2C_config_t* config)
{
  uint32_t I2C_status = I2Cx->CONFIG0 & 0x01UL;  
  I2Cx->CONFIG0 &= ~0x01UL;
  I2Cx->CONFIG1 = config->masterSlaveMode | (config->restart << 0x02) | (config->speedMode << 0x06) | (config->addrBitMode << 0x09);
  I2Cx->SLAVE_ADDR = config->localAddr;  
  I2Cx->CONFIG0 |= I2C_status;
}

void I2C_FIFOLevelSet(I2C_TypeDef* I2Cx, I2C_FIFOParam_t* config)
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

void I2C_DMAWatermarkSet(I2C_TypeDef* I2Cx, I2C_DMAParam_t* config)
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

