#ifndef VL6180X_DRIVER_H_
#define VL6180X_DRIVER_H_

#include <stdio.h>

#define LOG_PRINT 1

#if LOG_PRINT
#define i2c_print(x) printf(x)
#else
#define i2c_print(x) 
#endif


#if true
#define BIG_ENDIAN
#else
#define LITTLE_ENDIAN
#endif

typedef enum
{
  NO_ERR,
  ERR_BUSY,
  ERR_FIFO_FULL
}i2c_errType_t;

typedef enum
{
  I2C_READ_SINGLE_REG = 0x03,
  I2C_WRITE_SINGLE_REG,
  I2C_READ_MULTIPLE_REG,
  I2C_WRITE_MULTIPLE_REG
}i2c_operate_t;

typedef int opt_times_t;

typedef enum
{
  IDLE_OP,
  TRANSFER_DEV_ADDR,
  TRANSFER_REG_ADDR,
  READ_SINGLE_OP,
  WRITE_SINGLE_OP,
  READ_MULTIPLE_OP,
  WRITE_MULTIPLE_OP
}fsm_state_t;

typedef enum
{
  I2C_OK,
  I2C_ACK,
  I2C_NACK,
  I2C_START,
  I2C_RESTART,
  I2C_STOP,
  I2C_OVERFLOW
}i2c_status_t;

#define I2C_WRITE_LEN 32
#define I2C_READ_LEN 32

typedef struct fsm_struct{
  I2C_TypeDef* i2c_dev;
  
  fsm_state_t state;
  i2c_operate_t opt;
  opt_times_t cycle;
  i2c_errType_t err;
  
  uint16_t target_addrInfo;
  uint16_t target_addrBytes;
  uint16_t reg_addrInfo;
  uint16_t reg_addrBytes;
  
  uint8_t transmit_buffer[I2C_WRITE_LEN];
  uint8_t receive_buffer[I2C_READ_LEN];
  uint8_t transmit_len;
  uint8_t receive_len;
  
  uint16_t index;
  
  void (*i2c_opt_handler)(struct fsm_struct* port);
}fsm_struct_t;

typedef void (*i2c_handler_t)(struct fsm_struct* port);

typedef struct
{
  I2C_TypeDef* i2c_dev;
  
  i2c_operate_t opt;
  opt_times_t cycle;
  
  uint16_t target_addrInfo;
  uint8_t target_addrBytes;
  uint16_t reg_addrInfo;
  uint8_t reg_addrBytes;
  
  uint8_t transmit_len;
  uint8_t* transmit_buffer;
  
  void (*i2c_opt_handler)(struct fsm_struct* port);
}i2c_optConfig_t;

void I2C_Dev_Operate(fsm_struct_t* port,i2c_optConfig_t* config);
void I2C_FSM_Service(fsm_struct_t* port,i2c_status_t status);

#endif
