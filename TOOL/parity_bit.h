#ifndef PARITY_BIT_H_
#define PARITY_BIT_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define test 0

bool Byte_parityBitCheck(uint8_t data_byte);
uint8_t Byte_parityBitGenerate(uint8_t data_byte);

bool Word_parityBitCheck(uint16_t data_word);
void Word_parityBitGenerate(uint16_t* data_word);

bool Dword_parityBitCheck(uint32_t data_dword);
void Dword_parityBitGenerate(uint32_t* data_dword);

#if test

void Byte_parity_test(void);
void word_parity_test(void);
void dword_parity_test(void);

#endif

#endif
