#pragma once

#include <assert.h>
#include <stdint.h>
#include <string.h>

#ifndef NDBUG
#include <stdio.h>
#endif

#include "const.h"

const uint64_t uint64_set[64];
const uint64_t uint64_reset[64];
const unsigned uint64_counts[65536];



// returns 64 if b==0ull, returns most significant bit otherwise
unsigned uint64_first_index(uint64_t b);

// returns index of the only set bit in b
unsigned uint64_only_bit_index(uint64_t b);

uint64_t uint64_first_bit(uint64_t b);

// returns number of set bits
unsigned uint64_count(uint64_t b);

#ifdef NDEBUG
#define BITSET_DEBUG_DECLARE(SIZE)
#else
#define BITSET_DEBUG_DECLARE(SIZE)\
void bits##SIZE##_print(const struct bits##SIZE *bits);
#endif

#define BITSET_DECLARE(SIZE)\
struct bits##SIZE{\
    uint64_t data[1+((SIZE-1)/64)];\
};\
BITSET_DEBUG_DECLARE(SIZE)\
void bits##SIZE##_init(struct bits##SIZE *bits);\
void bits##SIZE##_clear(struct bits##SIZE *bits);\
void bits##SIZE##_copy(const struct bits##SIZE *bits,struct bits##SIZE *copy);\
bool bits##SIZE##_test(const struct bits##SIZE *bits,unsigned offset);\
unsigned bits##SIZE_count(const struct bits##SIZE *bits);\
bool bits##SIZE_equals(const struct bits##SIZE *lhs,const struct bits##SIZE *rhs);\
void bits##SIZE##_test_validity(const struct bits##SIZE *bits);


#ifdef NDEBUG
#define BITSET_DEBUG_DEFINE(SIZE)\
void bits##SIZE##_test_validity(const struct bits##SIZE *bits){\
    (void)bits;\
}
#else
#define BITSET_DEBUG_DEFINE(SIZE)\
void bits##SIZE##_print(const struct bits##SIZE *bits){\
    for(unsigned i=0;i<SIZE;++i){\
        if(i % 16 == 0){\
            printf("%d\t",i);\
        }\
        else if((i % 16) % 4 == 0){\
            putchar(' ');\
        }\
        putchar(bits##SIZE##_test(bits,i) ? '1' : '0');\
        if(i % 16 == 15 ){\
            putchar('\n');\
        }\
    }\
    putchar('\n');\
}\
void bits##SIZE##_test_validity(const struct bits##SIZE *bits){\
    if(SIZE % 64 == 0){\
        return;\
    }\
    uint64_t last = bits->data[SIZE / 64];\
    last <<= (SIZE % 64);\
    assert(last == 0ull);\
}
#endif


#define BITSET_DEFINE(SIZE)\
BITSET_DEBUG_DEFINE(SIZE)\
void bits##SIZE##_init(struct bits##SIZE *bits){\
    bits##SIZE##_clear(bits);\
}\
void bits##SIZE##_clear(struct bits##SIZE *bits){\
    memset(bits,0,sizeof(*bits));\
    bits##SIZE##_test_validity(bits);\
}\
void bits##SIZE##_copy(const struct bits##SIZE *bits,struct bits##SIZE *copy){\
    bits##SIZE##_test_validity(bits);\
    memcpy(copy,bits,sizeof(*bits));\
    bits##SIZE##_test_validity(copy);\
}\
bool bits##SIZE##_test(const struct bits##SIZE *bits,unsigned offset){\
    assert(offset < SIZE);\
    bits##SIZE##_test_validity(bits);\
    return bits->data[offset/64] & uint64_set[offset%64];\
}\
unsigned bits##SIZE_count(const struct bits##SIZE *bits){\
    bits##SIZE##_test_validity(bits);\
    unsigned total = 0;\
    for(int i=0; i < 1+((SIZE-1)/64); ++i){\
        total += uint64_count(bits->data[i]);\
    }\
    return total;\
}\
bool bits##SIZE_equals(const struct bits##SIZE *lhs,const struct bits##SIZE *rhs){\
    bits##SIZE##_test_validity(lhs);\
    bits##SIZE##_test_validity(rhs);\
    return memcmp(lhs,rhs,sizeof(*lhs)) == 0;\
}



BITSET_DECLARE(235);