#pragma once
#include <stdint.h>
#include <stddef.h>

void bitsn_scramble(uint8_t* bytes, size_t N);
void bitsn_un_scramble(uint8_t* bytes, size_t N);
void bitsn_pseudo_hadamard(uint8_t* a, uint8_t* b);
void bitsn_inv_pseudo_hadamard(uint8_t* a, uint8_t* b);
