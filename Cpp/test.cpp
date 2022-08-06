#include <cstddef>
#include <cstring>
#include "bitsnarl.hpp"

void test_hadamard() {
    for(int a = 0; a < 256; a++) {
        for(int b = 0; b < 256; b++) {
            if(a == 0 && b == 0) continue;
            std::uint8_t a_orig = a;
            std::uint8_t b_orig = b;
            bitsn::pseudo_hadamard(a_orig, b_orig);
            bitsn::pseudo_hadamard(a_orig, b_orig);
            if(a == a_orig && b == b_orig) {
                printf("pseudo_hadamard yield same result (%d, %d) => (%d, %d)\n", a, b, a_orig, b_orig);
            }
            bitsn::inv_pseudo_hadamard(a_orig, b_orig);
            bitsn::inv_pseudo_hadamard(a_orig, b_orig);
            if(!(a_orig == a && b_orig == b)) {
                printf("pseudo_hadamard not bijective at (%d, %d)\n", a, b);
            }
        }
    }
}

#define N 4000
void test_scramble_identity() {
    std::array<std::uint8_t, N> bytes_orig, bytes_copy;
    for(int i = 0; i < N; i++) {
        bytes_orig[i] = rand() % 255;
    }
    std::memcpy(bytes_copy.begin(), bytes_orig.begin(), N);
    bitsn::scramble(bytes_orig);
    bitsn::un_scramble(bytes_orig);
    for(int i = 0; i < N; i++) {
        if(bytes_orig[i] != bytes_copy[i]) {
            printf("diff at %i-th: %d\n", i, bytes_copy[i]);
        }
    }
}

void test_scramble_error_spread() {
    double same_rate = 0.0;
    double avg_same_rate = 0.0;

    std::array<std::uint8_t, N> bytes_orig, bytes_scrambled;
    for(int i = 0; i < N; i++) {
        bytes_orig[i] = rand() % 255;
    }
    memcpy(bytes_scrambled.begin(), bytes_orig.begin(), N);
    bitsn::scramble(bytes_scrambled);
    for(int p = 0; p < N; p++) { //error at p
        std::array<uint8_t, N> bytes_dirty;
        memcpy(bytes_dirty.begin(), bytes_scrambled.begin(), N);
        bytes_dirty[p] += 7; //inject some error
        bitsn::un_scramble(bytes_dirty);
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

int main() {
    test_hadamard();
    test_scramble_identity();
    test_scramble_error_spread();
}
