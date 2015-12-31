#include "game_config.h"

void trexo_game_config_on_new_game(
    struct trexo_game_config *config
){
   trexo_game_config_show_updated_field(config);
}

void trexo_game_config_init(
    struct trexo_game_config *config,
    struct trexo_main_window *window
){
    config->window = window;
    trexo_game_config_on_new_game(config);
    config->current = config->redo_max = 0;
    config->history = malloc((TREXO_MAX_MOVES+1) * sizeof(config->history));
}

void trexo_game_config_show_updated_field(
    const struct trexo_game_config* config
){
    const struct trexo_game_state* state = config->history + config->current;
    trexo_main_window_update_fields(config->window,state);
}

void trexo_game_config_process_click(
    struct trexo_game_config *config,
    int index,
    int button
){
    (void)button;
    struct trexo_game_state *state = config->history + config->current;
    struct trexo_game_state *next = state + 1;
    *next = *state;
    if(state->first_half_index == -1){
        if(!trexo_game_state_put_first_half(
            next,
            0,
            index
        )){
            return;
        }
    }
    else{
        if(!trexo_game_state_put_second_half(
            next,
            index
        )){
            return;
        }
    }

    //trexo_game_config_on_any_move(config,next);
    trexo_game_config_show_updated_field(config);
}


void trexo_game_config_on_any_move(
    struct trexo_game_config *config,
    const struct trexo_board *child
){
    (void)config;
    (void)child;
    /*struct trexo_game_state* s = trexo_game_config_get_state(gc);
    // WARNING THIS DOESNT WORK WITH GARRAY
    (s+1)->discs = *child;
    (s+1)->turn = s->turn; 
    game_state_update_turn(s+1);
    gc->current = gc->redo_max = gc->current + 1;
    trexo_game_config_show_updated_field(gc);
    if(board_test_game_ended(&(s+1)->discs)){
        trexo_game_config_on_ended(gc);
    }*/
}

void trexo_game_config_redo_move(
    struct trexo_game_config *config
){
    int cur = config->current + 1;
    if(cur < config->redo_max){
        config->current = cur;
    }
}

void trexo_game_config_undo_move(
    struct trexo_game_config *config
){
    int cur = config->current -1;
    while(cur >= 0){
        config->current = cur;
    }
}

void trexo_game_config_on_ended(
    const struct trexo_game_config *config
){
    (void)config;
    printf("%s","Game over!\n");
}

