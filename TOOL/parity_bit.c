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

void Byte_parityBitGenerate(uint8_t* data_byte)
{
  uint8_t count = 0;
  
  for(int i = 0;i < 7;i++)
  {
    if(*data_byte & (0x01 << i))
    {
      count++;
    }
  }
  
  if(count % 2)
  {
    *data_byte |= 1 << 7;
  }
  else
  {
    *data_byte &= ~(1 << 7);
  }
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
