#pragma once

#include "board.h"

enum trexo_directions{
    NEUTRAL = 0,
    UP = 1,
    DOWN = 2,
    LEFT = 3,
    RIGHT = 4
};


struct trexo_game_state{
    struct trexo_board board;
    enum trexo_directions directions[TREXO_NUM_FIELDS];
    int first_half_index;
};

void trexo_game_state_init(
    struct trexo_game_state *state
);

void trexo_game_state_copy(
    const struct trexo_game_state *state,
    struct trexo_game_state *copy
);

void trexo_game_state_put_first_half(
    struct trexo_game_state *state,
    bool is_x,
    int field_index
);

void trexo_game_state_put_second_half(
    struct trexo_game_state *state,
    bool is_x,
    int field_index
);

void game_state_switch_turn(
    struct trexo_game_state *state
);