#pragma once

#include <stdio.h>

#define TREXO_FIELD_SIDE 10
#define TREXO_NUM_FIELDS (TREXO_FIELD_SIDE * TREXO_FIELD_SIDE)

struct trexo_field{
	int height,brick_id,is_x;
};

void trexo_field_init(
	struct trexo_field *field,
	int height,
	int brick_id,
	int is_x
);

// -------------------------------

struct trexo_board{
	struct trexo_field fields[TREXO_NUM_FIELDS];
	int next_brick_id;
};

void trexo_board_init(
	struct trexo_board *board
);

void trexo_board_print(
	const struct trexo_board *board
);

void trexo_board_get_children(
	const struct trexo_board *board,
	struct trexo_board *output_start,
	struct trexo_board **output_end
);