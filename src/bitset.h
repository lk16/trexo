#pragma once

#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "const.h"

const uint64_t uint64_set[64];
const uint64_t uint64_reset[64];
const int uint64_counts[65536];



// returns 64 if b==0ull, returns most significant bit otherwise
int uint64_first_index(uint64_t b);

// returns index of the only set bit in b
int uint64_only_bit_index(uint64_t b);

uint64_t uint64_first_bit(uint64_t b);

// returns number of set bits
int uint64_count(uint64_t b);


#define BITSET_DECLARE(SIZE)\
struct bits##SIZE{\
    uint64_t data[1+((SIZE-1)/64)];\
};\
void bits##SIZE##_init(struct bits##SIZE *bits);\
void bits##SIZE##_clear(struct bits##SIZE *bits);\
void bits##SIZE##_copy(const struct bits##SIZE *bits,struct bits##SIZE *copy);\
void bits##SIZE##_print(const struct bits##SIZE *bits);\
bool bits##SIZE##_test(const struct bits##SIZE *bits,unsigned offset);


#define BITSET_DEFINE(SIZE)\
void bits##SIZE##_init(struct bits##SIZE *bits){\
    bits##SIZE##_clear(bits);\
}\
void bits##SIZE##_clear(struct bits##SIZE *bits){\
    memset(bits,0,sizeof(*bits));\
}\
void bits##SIZE##_copy(const struct bits##SIZE *bits,struct bits##SIZE *copy){\
    memcpy(copy,bits,sizeof(*bits));\
}\
void bits##SIZE##_print(const struct bits##SIZE *bits){\
    for(unsigned i=0;i<SIZE;++i){\
        if(i % 16 == 0){\
            printf("%d\t",i);\
        }\
        else if((i % 16) % 4 == 0){\
            putchar(' ');\
        }\
        putchar(bits##SIZE##_test(bits,i) ? '1' : '0');\
        if(i % 16 == 15){\
            putchar('\n');\
        }\
    }\
    putchar('\n');\
}\
bool bits##SIZE##_test(const struct bits##SIZE *bits,unsigned offset){\
    assert(offset < SIZE);\
    return bits->data[offset/64] & uint64_set[offset%64];\
}



BITSET_DECLARE(235);