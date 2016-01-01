#pragma once

#include <stdio.h>

#include "const.h"

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

// print to stdout
void trexo_board_print(
    const struct trexo_board *board
);

// put children in output_start
// makes output_end point to one past the last child
void trexo_board_get_children(
    struct trexo_board *board,
    struct trexo_board *output_start,
    struct trexo_board **output_end
);

// returns TRUE if move is valid 
bool trexo_board_is_valid_move_first_half(
    const struct trexo_board *board,
    int field_index
);

// returns TRUE if move is valid 
bool trexo_board_is_valid_move_second_half(
    const struct trexo_board *board,
    int first_field_id,
    int second_field_id
);

// returns TRUE if this move is valid 
// when FALSE is returned, board is not modified
bool trexo_board_try_putting_half_brick(
    struct trexo_board *board,
    int field_index,
    int is_x
);

// returns field_id of unfinished (half) brick if any, else -1
int trexo_board_get_unfinished_brick_field_id(
    const struct trexo_board *board
);