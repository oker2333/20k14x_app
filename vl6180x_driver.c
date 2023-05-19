#include <string.h>

#include "z20k14x_i2c.h"

#include "vl6180x_driver.h"


#define FSM_FIFO_SIZE 10

fsm_struct_t fsm_fifo[FSM_FIFO_SIZE];


void I2C_FSM_Service(fsm_struct_t* port,i2c_status_t status)
{
  switch(port->state)
  {
    case IDLE_OP:
      /* 关闭I2C发送中断 */
      I2C_intEnable(port->i2c_dev, I2C_TX_EMPTY_IE, Disable);
      break;

    case TRANSFER_DEV_ADDR:

      break;

    case TRANSFER_REG_ADDR:
        if(status != I2C_OK)
        {
          I2C_intEnable(port->i2c_dev, I2C_TX_EMPTY_IE, Disable);
          port->state = IDLE_OP;
        }
        else if(port->reg_addrBytes != 0x00)
        {
          while((I2C_TxFIFOCountGet(port->i2c_dev) != I2C_TX_FIFO_DEPTH) && (port->index < port->reg_addrBytes))
          {
            I2C_transmitData(port->i2c_dev, ((uint8_t*)(&port->reg_addrInfo))[port->index++],I2C_RESET_STOP_DIS);
          }
          
          if(port->index < port->reg_addrBytes)
          {
            port->state = TRANSFER_REG_ADDR;
          }
          else
          {
            port->index = 0x00;
            port->state = (fsm_state_t)port->opt;
          }
        }
        
      break;

    case READ_SINGLE_OP:

      break;

    case WRITE_SINGLE_OP:
        if(status != I2C_OK)
        {
          I2C_intEnable(port->i2c_dev, I2C_TX_EMPTY_IE, Disable);
          port->state = IDLE_OP;
        }
        else if(port->transmit_len != 0x00)
        {
          while((I2C_TxFIFOCountGet(port->i2c_dev) != I2C_TX_FIFO_DEPTH) && (port->index < port->transmit_len))
          {
            I2C_restartStop_t cmd = I2C_RESET_STOP_DIS;
            
            if(port->index == (port->transmit_len - 1))
            {
              cmd = I2C_STOP_EN;
            }
            I2C_transmitData(port->i2c_dev, ((uint8_t*)(&port->transmit_buffer))[port->index++],cmd);
          }
          
          if(port->index < port->transmit_len)
          {
            port->state = WRITE_SINGLE_OP;
          }
          else
          {
            port->index = 0x00;
            port->state = IDLE_OP;
            
            if(port->i2c_opt_handler)
            {
              port->i2c_opt_handler(port);
            }
            
            I2C_intEnable(port->i2c_dev, I2C_TX_EMPTY_IE, Disable);
          }
        }
      break;

    case READ_MULTIPLE_OP:
      
      break;

    case WRITE_MULTIPLE_OP:
      
      break;

    default:
      
      break;
  }
}

void I2C_Dev_Operate(fsm_struct_t* port,i2c_optConfig_t* config)      //将结构体copy到fifo队列中
{
  port->i2c_dev = config->i2c_dev;
  
  port->state = TRANSFER_REG_ADDR;
  port->opt = config->opt;
  
  port->target_addrInfo = config->target_addrInfo;
  port->target_addrBytes = config->target_addrBytes;

  port->reg_addrInfo = config->reg_addrInfo;
  port->reg_addrBytes = config->reg_addrBytes;

  if(config->transmit_len != 0)
  {
    port->transmit_len = config->transmit_len;
    memcpy(port->transmit_buffer,config->transmit_buffer,config->transmit_len);
  }
  
  port->receive_len = 0x00;
  
  port->index = 0x00;
  
  port->i2c_opt_handler = config->i2c_opt_handler;

  /*开启I2C Tx空中断*/
  I2C_intEnable(port->i2c_dev, I2C_TX_EMPTY_IE, Enable);
}

