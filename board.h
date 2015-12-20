#pragma once

const int trexo_field_side = 10;

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
	struct trexo_field fields[trexo_field_side * trexo_field_size];
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