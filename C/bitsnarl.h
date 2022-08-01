#pragma once
#include <stdint.h>
#include <stddef.h>

void init_scramble();
void pseudo_hadamard(uint8_t* a, uint8_t* b);
void inv_pseudo_hadamard(uint8_t* a, uint8_t* b);
void scramble(size_t N, uint8_t* bytes);
void inv_scramble(size_t N, uint8_t* bytes);
