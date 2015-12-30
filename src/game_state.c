#include "game_state.h"

void trexo_game_state_init(
    struct trexo_game_state* state
){
    trexo_board_init(&state->board);
    for(int i=0; i<TREXO_NUM_FIELDS; ++i){
        state->directions[i] = TREXO_NEUTRAL;
    }
    state->first_half_index = -1;
    state->first_half_is_x = 0;
    state->turn = 0;
}

int trexo_game_state_put_first_half(
    struct trexo_game_state *state,
    int is_x,
    int field_index
){
    if(!trexo_board_is_valid_move_first_half(&state->board,field_index)){
        return 0;
    }
    state->first_half_index = field_index;
    state->first_half_is_x = is_x;
    return 1;
}

int trexo_game_state_put_second_half(
    struct trexo_game_state *state,
    int second_half_index
){
    if(!trexo_board_is_valid_move_second_half(
        &state->board,state->first_half_index,
        second_half_index
    )){
        return 0;
    }
    int diff = state->first_half_index - second_half_index;
    if(diff == 1){
        state->directions[state->first_half_index] = TREXO_LEFT;
        state->directions[second_half_index] = TREXO_RIGHT;
    }
    else if(diff == -1){
        state->directions[state->first_half_index] = TREXO_RIGHT;
        state->directions[second_half_index] = TREXO_LEFT;
    }
    else if(diff == TREXO_FIELD_SIDE){
        state->directions[state->first_half_index] = TREXO_UP;
        state->directions[second_half_index] = TREXO_DOWN;
    }
    else if(diff == -TREXO_FIELD_SIDE){
        state->directions[state->first_half_index] = TREXO_DOWN;
        state->directions[second_half_index] = TREXO_UP;
    }
    else{
        printf("Uh oh diff = %d\n",diff);
        return 0;
    }

    trexo_field_init(
        state->board.fields + state->first_half_index,
        state->board.fields[state->first_half_index].height + 1,
        state->board.next_brick_id,
        state->first_half_is_x
    );

    trexo_field_init(
        state->board.fields + second_half_index,
        state->board.fields[second_half_index].height + 1,
        state->board.next_brick_id,
        !state->first_half_is_x
    );

    ++state->board.next_brick_id;

    state->first_half_index = -1;
    state->first_half_is_x = 0;
    return 1;
}


void game_state_switch_turn(
    struct trexo_game_state *state
){
    state->turn = !state->turn;
}