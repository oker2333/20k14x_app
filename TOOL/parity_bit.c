#include "parity_bit.h"

/****************one byte****************/
bool Byte_parityBitCheck(uint8_t data_byte)
{
  bool ret = false;
  uint8_t count = 0;
  
  for(int i = 0;i < 8;i++)
  {
    if(data_byte & (0x01 << i))
    {
      count++;
    }
  }
  
  if((count % 0x02) == 0x00)
  {
    ret = true;
  }
  
  return ret;
}

uint8_t Byte_parityBitGenerate(uint8_t data_byte)
{
  uint8_t count = 0;
  
  for(int i = 0;i < 7;i++)
  {
    if(data_byte & (0x01 << i))
    {
      count++;
    }
  }
  
  if(count % 2)
  {
    data_byte |= 1 << 7;
  }
  else
  {
    data_byte &= ~(1 << 7);
  }
  
  return data_byte;
}

/****************two bytes****************/
bool Word_parityBitCheck(uint16_t data_word)
{
  bool ret = false;
  uint8_t count = 0;
  
  for(int i = 0;i < 16;i++)
  {
    if(data_word & (0x01 << i))
    {
      count++;
    }
  }
  
  if((count % 0x02) == 0x00)
  {
    ret = true;
  }
  
  return ret;
}

void Word_parityBitGenerate(uint16_t* data_word)
{
  uint8_t count = 0;
  
  for(int i = 0;i < 15;i++)
  {
    if(*data_word & (0x01 << i))
    {
      count++;
    }
  }
  
  if(count % 2)
  {
    *data_word |= 1 << 15;
  }
  else
  {
    *data_word &= ~(1 << 15);
  }
}

/****************four bytes****************/
bool Dword_parityBitCheck(uint32_t data_dword)
{
  bool ret = false;
  uint8_t count = 0;
  
  for(int i = 0;i < 32;i++)
  {
    if(data_dword & (0x01 << i))
    {
      count++;
    }
  }
  
  if((count % 0x02) == 0x00)
  {
    ret = true;
  }
  
  return ret;
}

void Dword_parityBitGenerate(uint32_t* data_dword)
{
  uint8_t count = 0;
  
  for(int i = 0;i < 31;i++)
  {
    if(*data_dword & (0x01 << i))
    {
      count++;
    }
  }
  
  if(count % 2)
  {
    *data_dword |= (0x01UL << 31);
  }
  else
  {
    *data_dword &= ~(0x01UL << 31);
  }
}

#if test

#include <math.h>

void dword_parity_test(void)
{
  for(long long i = 0;i < pow(2,(8 * sizeof(int32_t)));i++)
  {
    static int32_t value = 0x00;
    uint32_t value_parity = value;
    
    Dword_parityBitGenerate(&value_parity);
    
    if(!Dword_parityBitCheck(value_parity))
    {
      printf("[dword_parity_test]error value = 0x%x,value_parity = 0x%x\n",value,value_parity);
    }
    else
    {
      printf("[dword_parity_test]correct value = 0x%x,value_parity = 0x%x\n",value,value_parity);
    }
    value++;
  }
}

void word_parity_test(void)
{
  for(int i = 0;i < pow(2, (8 * sizeof(int16_t)));i++)
  {
    static int16_t value = 0x00;
    uint16_t value_parity = value;
    
    Word_parityBitGenerate(&value_parity);
    
    if(!Word_parityBitCheck(value_parity))
    {
      printf("[word_parity_test]error value = 0x%x,value_parity = 0x%x\n",value,value_parity);
    }
    else
    {
      printf("[word_parity_test]correct value = 0x%x,value_parity = 0x%x\n",value,value_parity);
    }
    
    value++;
  }
}

void Byte_parity_test(void)
{
  for(int i = 0;i < pow(2, (8 * sizeof(int8_t)));i++)
  {
    static int8_t value = 0x00;
    uint8_t value_parity = value;
    
    Byte_parityBitGenerate(&value_parity);
    
    if(!Byte_parityBitCheck(value_parity))
    {
      printf("[Byte_parity_test]error value = 0x%x,value_parity = 0x%x\n",value,value_parity);
    }
    else
    {
      printf("[Byte_parity_test]correct value = 0x%x,value_parity = 0x%x\n",value,value_parity);
    }
    
    value++;
  }
}

#endif

