#include <stdint.h>
#include <stddef.h>

static uint8_t GF_table[256], inv_GF_table[256];
void init_scramble() {
    int n = 1;
    // p(x) = x^8 + x^4 + x^3 + x^2 + 1
    const int poly_magic = (1 << 4) | (1 << 3) | (1 << 2) | 1;
    for(int i = 0; i < 255; i++) {
        GF_table[i%255] = (uint8_t)n;
        inv_GF_table[n] = (uint8_t)i;

        n = (n << 1); // treat overflow by x^8 = x^4 + x^3 + x^2 + 1
        n = ((n >> 8) * poly_magic) ^ (n & (uint8_t)255);
    }
    GF_table[255] = n;

    //make the map bijective
    GF_table[0] = 0;
    inv_GF_table[0] = 0;
    inv_GF_table[1] = 255;
}

#include <stdio.h>
void print_table() {
    for(int i = 0; i < 256; i++) {
        printf("%d-th, forward: %d, reverse: %d\n", i, GF_table[i], inv_GF_table[i]);
    }
}

//void check_bijective_table() {
//    for(int i = 0; i < 256; i++) {
//        if(i != inv_GF_table[GF_table[i]]) {
//            printf("not bijective at %d; GF_table[i] = %d, inv_GF_table[GF_table[i]] = %d\n", i, GF_table[i], inv_GF_table[GF_table[i]]);
//        }
//        if(i != GF_table[inv_GF_table[i]]) {
//            printf("not bijective at %d; GF_table[i] = %d, inv_GF_table[GF_table[i]] = %d\n", i, GF_table[i], inv_GF_table[GF_table[i]]);
//        }
//    }
//}

void pseudo_hadamard(uint8_t* a, uint8_t* b){
    uint8_t new_a = *a + *b;
    uint8_t new_b = *a + 2*(*b);
    *a = new_a;
    *b = new_b;
}

void inv_pseudo_hadamard(uint8_t* a, uint8_t* b) {
    uint8_t new_b = *b - *a;
    uint8_t new_a = 2*(*a) - *b;
    *a = new_a;
    *b = new_b;
}


void scramble(size_t N, uint8_t* bytes) {
    int step = 1;
    do {
        for(int i = 0; i < N; i++) {
            bytes[i] = GF_table[bytes[i]];
        }
        for(int i = 0; i < N; i++) {
            pseudo_hadamard(&bytes[i], &bytes[(i+step)%N]);
        }
        step *= 2;
    } while(step*2 <= N);
}

void inv_scramble(size_t N, uint8_t* bytes) {
    int step = 1;
    do {
        step *= 2;
    } while(step*2 <= N);
    step /= 2;

    do {
        for(int i = N-1; i >= 0; i--) {
            inv_pseudo_hadamard(&bytes[i], &bytes[(i+step)%N]);
        }
        for(int i = 0; i < N; i++) {
            bytes[i] = inv_GF_table[bytes[i]];
        }
        step /= 2;
    } while(step >= 1);
}
