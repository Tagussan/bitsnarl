#include <stdio.h>
#include <stdint.h>

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

void print_table() {
    for(int i = 0; i < 256; i++) {
        printf("%d-th, forward: %d, reverse: %d\n", i, GF_table[i], inv_GF_table[i]);
    }
}

void print_table_code() {
    //GF_table
    printf("For GF_table\n\n");
    printf("{\n");
    for(int i = 0; i < 256; i++) {
        printf("%3d", GF_table[i]);
        if(i != 255) {
            printf(",");
        }
        if(i % 16 == 15) {
            printf("\n");
        } else {
            printf(" ");
        }
    }
    printf("};\n\n");

    //inv_GF_table
    printf("For inv_GF_table\n\n");
    printf("{\n");
    for(int i = 0; i < 256; i++) {
        printf("%3d", inv_GF_table[i]);
        if(i != 255) {
            printf(",");
        }
        if(i % 16 == 15) {
            printf("\n");
        } else {
            printf(" ");
        }
    }
    printf("};");
}

void check_bijective_table() {
    for(int i = 0; i < 256; i++) {
        if(i != inv_GF_table[GF_table[i]]) {
            printf("not bijective at %d; GF_table[i] = %d, inv_GF_table[GF_table[i]] = %d\n", i, GF_table[i], inv_GF_table[GF_table[i]]);
        }
        if(i != GF_table[inv_GF_table[i]]) {
            printf("not bijective at %d; GF_table[i] = %d, inv_GF_table[GF_table[i]] = %d\n", i, GF_table[i], inv_GF_table[GF_table[i]]);
        }
    }
}
