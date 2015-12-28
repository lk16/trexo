#pragma once

#include <assert.h>
#include <string.h>
#include <stdio.h>

#include <gtk/gtk.h>

#include <glib.h>

#include "board.h"
#include "clickable_image.h"
#include "game_state.h"

void game_state_update_turn(
    struct trexo_game_state* gs
);

void game_state_print(
    const struct trexo_game_state* gs,
    FILE* file
);



struct game_state* game_state_get_children(
    const struct trexo_game_state* gs,
    struct game_state* out
);

struct main_window;

void main_window_update_fields(
    struct main_window*,
    const struct trexo_game_state*
);

struct trexo_game_config{
    //struct player players[2];
    GArray *state_history;
    int current,redo_max;
    struct trexo_game_state *state;
    struct main_window* window;
};

void trexo_game_config_init(
    struct trexo_game_config* gc,
    struct main_window* mw
);

void trexo_game_config_on_new_game(
    struct trexo_game_config* gc
);

void trexo_game_config_on_ended(
    const struct trexo_game_config* gc
);

void trexo_game_config_on_any_move(
    struct trexo_game_config* gc,
    const struct trexo_board* child
);

void trexo_game_config_show_updated_field(
    const struct trexo_game_config* gc
);

int trexo_game_config_timeout(
    struct trexo_game_config* gc
);

void trexo_game_config_process_click(
    struct trexo_game_config* gc,
    int index,
    int button
);