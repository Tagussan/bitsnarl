#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "bitsnarl.h"

void test_hadamard() {
    for(int a = 0; a < 256; a++) {
        for(int b = 0; b < 256; b++) {
            if(a == 0 && b == 0) continue;
            uint8_t a_orig = a;
            uint8_t b_orig = b;
            bitsn_pseudo_hadamard(&a_orig, &b_orig);
            bitsn_pseudo_hadamard(&a_orig, &b_orig);
            if(a == a_orig && b == b_orig) {
                printf("pseudo_hadamard yield same result (%d, %d) => (%d, %d)\n", a, b, a_orig, b_orig);
            }
            bitsn_inv_pseudo_hadamard(&a_orig, &b_orig);
            bitsn_inv_pseudo_hadamard(&a_orig, &b_orig);
            if(!(a_orig == a && b_orig == b)) {
                printf("pseudo_hadamard not bijective at (%d, %d)\n", a, b);
            }
        }
    }
}

#define N 4000
void test_scramble_identity() {
    uint8_t bytes_orig[N], bytes_copy[N];
    for(int i = 0; i < N; i++) {
        bytes_orig[i] = rand() % 255;
    }
    memcpy(bytes_copy, bytes_orig, N);
    bitsn_scramble(N, bytes_orig);
    bitsn_un_scramble(N, bytes_orig);
    for(int i = 0; i < N; i++) {
        if(bytes_orig[i] != bytes_copy[i]) {
            printf("diff at %i-th: %d\n", i, bytes_copy[i]);
        }
    }
}

void test_scramble_error_spread() {
    double same_rate = 0.0;
    double avg_same_rate = 0.0;

    uint8_t bytes_orig[N], bytes_scrambled[N];
    for(int i = 0; i < N; i++) {
        bytes_orig[i] = rand() % 255;
    }
    memcpy(bytes_scrambled, bytes_orig, N);
    bitsn_scramble(N, bytes_scrambled);
    for(int p = 0; p < N; p++) { //error at p
        uint8_t bytes_dirty[N];
        memcpy(bytes_dirty, bytes_scrambled, N);
        bytes_dirty[p] += 7; //inject some error
        bitsn_un_scramble(N, bytes_dirty);
        int same_count = 0;
        for(int i = 0; i < N; i++) {
            if(bytes_dirty[i] == bytes_scrambled[i]) {
                same_count++;
            }
        }
        same_rate = (double)same_count / (double)N;
        avg_same_rate += same_rate;
    }
    double error = avg_same_rate / (double)N;
    printf("Probability of getting same bytes after bit error: %f\n", error);
    printf("Probability of getting same bytes at random: 1/256=%f\n", 1.0/256.0);
}

void disp_byte(uint8_t byte) {
    for(int i = 0; i < 8; i++) {
        printf("%d", !!((byte << i) & 0x80));
    }
}

void disp_bytes(size_t n, uint8_t* bytes) {
    for(int i = 0; i < n; i++) {
        disp_byte(bytes[i]);
        if(i != n-1) {
            putchar(' ');
        } else {
            putchar('\n');
        }
    }
}

void show_example() {
    // scramble and recover
    uint8_t bytes_orig[8];
    for(int i = 0; i < 8; i++) {
        bytes_orig[i] = rand() % 255;
    }
    printf("Original\n");
    disp_bytes(8, bytes_orig);
    bitsn_scramble(8, bytes_orig);
    printf("Scrambled\n");
    disp_bytes(8, bytes_orig);
    bitsn_un_scramble(8, bytes_orig);
    printf("Un-scrambled\n");
    disp_bytes(8, bytes_orig);

    printf("\nOriginal\n");
    disp_bytes(8, bytes_orig);
    bitsn_scramble(8, bytes_orig);
    printf("Scrambled\n");
    disp_bytes(8, bytes_orig);
    bytes_orig[1] += 1;
    printf("With Error\n");
    disp_bytes(8, bytes_orig);
    bitsn_un_scramble(8, bytes_orig);
    printf("Un-scrambled\n");
    disp_bytes(8, bytes_orig);
}


int main() {
    srand((unsigned int)time(NULL));
    test_hadamard();
    test_scramble_identity();
    test_scramble_error_spread();
    show_example();
    return 0;
}
