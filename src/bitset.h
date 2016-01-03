#pragma once

#include <stdint.h>

#include "macros.h"

const uint64_t uint64_set[64];
const uint64_t uint64_reset[64];
const uint64_t uint64_before[64];
const uint64_t uint64_after[64];
const int uint64_counts[65536];

// returns 64 if b==0ull, returns most significant bit otherwise
int uint64_first_index(uint64_t b);

// returns index of the only set bit in b
int uint64_only_bit_index(uint64_t b);

// returns 64 if b==0ull, returns most significant bit otherwise
int uint64_last_index(uint64_t b);

uint64_t uint64_first_bit(uint64_t b);

// returns number of set bits
int uint64_count(uint64_t b);





void uint64_reset_before(uint64_t *b,int n);

void uint64_reset_after(uint64_t *b,int n);

uint64_t uint64_is_subset_of_mask(
	uint64_t set,
	uint64_t subset
);