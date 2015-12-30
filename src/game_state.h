#pragma once

#include <stdio.h>

#include "board.h"

enum trexo_directions{
    TREXO_NEUTRAL = 0,
    TREXO_UP = 1,
    TREXO_DOWN = 2,
    TREXO_LEFT = 3,
    TREXO_RIGHT = 4
};


struct trexo_game_state{
    struct trexo_board board;
    enum trexo_directions directions[TREXO_NUM_FIELDS];
    int first_half_index,first_half_is_x,turn;
};

void trexo_game_state_init(
    struct trexo_game_state *state
);

int trexo_game_state_put_first_half(
    struct trexo_game_state *state,
    int is_x,
    int field_index
);

int trexo_game_state_put_second_half(
    struct trexo_game_state *state,
    int second_half_index
);

void game_state_switch_turn(
    struct trexo_game_state *state
);

void game_state_print(
    const struct trexo_game_state *state,
    FILE *file
);
