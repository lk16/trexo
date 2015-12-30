#include "game_config.h"

void trexo_game_config_on_new_game(
    struct trexo_game_config *gc
){
   trexo_game_config_show_updated_field(gc);
}

void trexo_game_config_init(
    struct trexo_game_config *config,
    struct trexo_main_window *window
){
    config->window = window;
    trexo_game_config_on_new_game(config);
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
    (void)config;
    (void)button;
    (void)index;
    /*(void)button;
    struct trexo_game_state* state = &g_array_index(gc->state_history,struct trexo_game_state,gc->current);
    if(!trexo_board_is_valid_move(&state->discs,index)){
        return;
    }
    struct trexo_board child = state->discs;
    board_do_move(&child,index);
    trexo_game_config_on_any_move(gc,&child);
    
    trexo_game_config_show_updated_field(gc);*/

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

