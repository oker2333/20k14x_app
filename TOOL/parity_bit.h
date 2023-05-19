#ifndef PARITY_BIT_H_
#define PARITY_BIT_H_

#include <stdbool.h>
#include <stdint.h>

bool Byte_parityBitCheck(uint8_t data_byte);
void Byte_parityBitGenerate(uint8_t* data_byte);

bool Word_parityBitCheck(uint16_t data_word);
void Word_parityBitGenerate(uint16_t* data_word);

bool Dword_parityBitCheck(uint32_t data_dword);
void Dword_parityBitGenerate(uint32_t* data_dword);

#endif
