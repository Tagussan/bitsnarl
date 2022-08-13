#include <stdio.h>
#include <stdint.h>
#include "bitsnarl.h"

void disp_byte(uint8_t byte) {
    for(int i = 0; i < 8; i++) {
        printf("%d", !!((byte << i) & 0x80));
    }
}

void disp_bytes(uint8_t* bytes, size_t n) {
    for(int i = 0; i < n; i++) {
        disp_byte(bytes[i]);
        if(i != n-1) {
            putchar(' ');
        } else {
            putchar('\n');
        }
    }
}

void disp_bytes_as_char(uint8_t* bytes, size_t n) {
    for(int i = 0; i < n; i++) {
        // if the byte is not a character, then skip
        if(32 <= bytes[i] && bytes[i] <= 126) {
            putchar(bytes[i]);
        }
        if(i != n-1) {
            putchar(' ');
        } else {
            putchar('\n');
        }
    }
}

int main() {
    uint8_t data[] = "Love";
    int len = sizeof(data)/sizeof(char) - 1; // ignore last null char for example

    printf("Original\n");
    disp_bytes(data, len); // display original data as bits
    disp_bytes_as_char(data, len); // display the data as char

    printf("-----------------------------\n");
    bitsn_scramble((uint8_t*)data, len); // scramble the data
    printf("Scrambled\n");
    disp_bytes(data, len); // display scrambled data as bits

    bitsn_un_scramble((uint8_t*)data, len); // un-scramble the data
    printf("Un-scrambled\n");
    disp_bytes(data, len); // display the restored data; should be same as the original
    printf("-----------------------------\n");

    printf("-----------------------------\n");
    bitsn_scramble((uint8_t*)data, len); // scramble the data
    printf("Scrambled\n");
    disp_bytes(data, len); // display scrambled data as bits

    data[1] += 2; // contaminate with a bit error
    printf("Error\n");
    disp_bytes(data, len); // data with error

    printf("Un-scrambled\n");
    bitsn_un_scramble((uint8_t*)data, len); // display the un-scrambled data; should be quite different from the original
    disp_bytes(data, len);
    disp_bytes_as_char(data, len);
    return 0;
}
