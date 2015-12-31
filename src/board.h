#pragma once

#include <stdio.h>

#define TREXO_FIELD_SIDE 6
#define TREXO_NUM_FIELDS (TREXO_FIELD_SIDE * TREXO_FIELD_SIDE)
#define TREXO_MAX_CHILDREN (4 * TREXO_FIELD_SIDE * (TREXO_FIELD_SIDE - 1))

struct trexo_field{
    int height,brick_id,is_x;
};

void trexo_field_init(
    struct trexo_field *field,
    int height,
    int brick_id,
    int is_x
);

int trexo_field_is_valid_move(
    const struct trexo_field *lhs,
    const struct trexo_field *rhs
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
    struct trexo_board *board,
    struct trexo_board *output_start,
    struct trexo_board **output_end
);

int trexo_board_is_valid_move_first_half(
    const struct trexo_board *board,
    int field_index
);

int trexo_board_is_valid_move_second_half(
    const struct trexo_board *board,
    int first_field_id,
    int second_field_id
);

int trexo_try_putting_half_brick(
    struct trexo_board *board,
    int field_index,
    int is_x
);