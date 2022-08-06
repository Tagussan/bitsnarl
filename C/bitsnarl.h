#pragma once
#include <stdint.h>
#include <stddef.h>

void bitsn_scramble(size_t N, uint8_t* bytes);
void bitsn_un_scramble(size_t N, uint8_t* bytes);
void bitsn_pseudo_hadamard(uint8_t* a, uint8_t* b);
void bitsn_inv_pseudo_hadamard(uint8_t* a, uint8_t* b);
