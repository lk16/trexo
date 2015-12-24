#pragma once

#include <assert.h>
#include <string.h>
#include <stdio.h>

#include <gtk/gtk.h>

#include "board.h"
#include "clickable_image.h"

enum trexo_directions{
    NEUTRAL = 0,
    UP = 1,
    DOWN = 2,
    LEFT = 3,
    RIGHT = 4
};


struct trexo_game_state{
    struct trexo_board board;
    int directions[TREXO_NUM_FIELDS];
};


void game_state_init(struct game_state* gs);

void game_state_update_turn(struct game_state* gs);

void game_state_print(const struct game_state* gs,FILE* file);

void game_state_switch_turn(struct game_state* gs);

struct game_state* game_state_get_children(const struct game_state* gs,struct game_state* out);

struct main_window;

void main_window_update_fields(struct main_window*,const struct game_state*);

struct game_config{
    //struct player players[2];
    //struct game_state history[61];
    //int current,redo_max;
    struct trexo_game_state *state;
    struct main_window* window;
;

void game_config_init(struct game_config* gc,struct main_window* mw);

void game_config_on_new_game(struct game_config* gc);

void game_config_on_ended(const struct game_config* gc);

void game_config_on_any_move(struct game_config* gc,const struct board* child);

void game_config_show_updated_field(const struct game_config* gc);

int game_config_timeout(struct game_config* gc);

void game_config_process_click(struct game_config* gc, int index,int button);