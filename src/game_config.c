#include "game_config.h"

void trexo_game_config_on_new_game(
    struct trexo_game_config *config
){
    trexo_board_init(config->history);
    trexo_game_config_show_updated_field(config);
}

void trexo_game_config_init(
    struct trexo_game_config *config,
    struct trexo_main_window *window
){
    config->window = window;
    config->current = config->redo_max = 0;
    config->history = malloc((TREXO_MAX_MOVES+1) * sizeof(config->history));
    trexo_game_config_on_new_game(config);
}

void trexo_game_config_show_updated_field(
    const struct trexo_game_config* config
){
    const struct trexo_board *board = config->history + config->current;
    trexo_main_window_update_fields(config->window,board);
}

void trexo_game_config_process_click(
    struct trexo_game_config *config,
    int index,
    int button
){
    (void)button;
    struct trexo_board *board = config->history + config->current;
    struct trexo_board *next = board + 1;
    *next = *board;
    
    if(trexo_board_try_putting_half_brick(
        next,
        index,
        0
    )){
        trexo_game_config_show_updated_field(config);
    }
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

