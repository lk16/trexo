#pragma once

#include <assert.h>
#include <malloc.h>
#include <string.h>
#include <stdio.h>


#include <gtk/gtk.h>

#include <glib.h>


#include "board.h"
#include "clickable_image.h"

#define TREXO_MAX_MOVES (1000)

struct trexo_game_config;
struct trexo_main_window;   

void trexo_main_window_update_fields(
    struct trexo_main_window *window,
    const struct trexo_board *board
);



struct trexo_game_config{
    struct trexo_board *history;
    int current,redo_max;
    struct trexo_main_window* window;
};

void trexo_game_config_init(
    struct trexo_game_config* gc,
    struct trexo_main_window* mw
);

void trexo_game_config_on_new_game(
    struct trexo_game_config* gc
);

void trexo_game_config_on_ended(
    const struct trexo_game_config* gc
);

void trexo_game_config_redo_move(
    struct trexo_game_config *config
);

void trexo_game_config_undo_move(
    struct trexo_game_config *config
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