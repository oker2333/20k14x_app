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

typedef struct
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

#define PERIPH_BASE     ((uint32_t)0x40000000) /*!< Peripheral base address in the alias region                                */

#define I2C0_BASE_ADDRESS       (PERIPH_BASE + 0x66000)
#define I2C1_BASE_ADDRESS       (PERIPH_BASE + 0x58000)

#define I2C0    ((I2C_TypeDef *) I2C0_BASE_ADDRESS)
#define I2C1    ((I2C_TypeDef *) I2C1_BASE_ADDRESS)

#endif

