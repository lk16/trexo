#include "game_config.h"

void trexo_game_config_on_new_game(
    struct trexo_game_config* gc
){
   trexo_game_config_show_updated_field(gc);
}

void trexo_game_config_init(
    struct trexo_game_config* gc,
    struct main_window* mw
){
    gc->window = mw;
    trexo_game_config_on_new_game(gc);
}

void trexo_game_config_show_updated_field(
    const struct trexo_game_config* gc
){
    const struct trexo_game_state* current = gc->state;
    main_window_update_fields(gc->window,current);
}

void trexo_game_config_process_click(struct trexo_game_config* gc, int index,int button)
{
    (void)button;
    struct trexo_game_state* state = &g_array_index(gc->state_history,struct trexo_game_state,gc->current);
    if(!board_is_valid_move(&state->discs,index)){
        return;
    }
    struct trexo_board child = state->discs;
    board_do_move(&child,index);
    trexo_game_config_on_any_move(gc,&child);
    
    trexo_game_config_show_updated_field(gc);
}


void trexo_game_config_on_any_move(struct trexo_game_config* gc,const struct board* child)
{
  struct trexo_game_state* s = trexo_game_config_get_state(gc);
  // WARNING THIS DOESNT WORK WITH GARRAY
  (s+1)->discs = *child;
  (s+1)->turn = s->turn; 
  game_state_update_turn(s+1);
  gc->current = gc->redo_max = gc->current + 1;
  trexo_game_config_show_updated_field(gc);
  if(board_test_game_ended(&(s+1)->discs)){
    trexo_game_config_on_ended(gc);
  }
}



void trexo_game_config_redo_move(struct trexo_game_config* gc)
{
  int cur = gc->current + 1;
  while(cur < gc->redo_max){
    if(gc->players[gc->history[cur].turn].type == PLAYER_HUMAN){
      gc->current = cur;
      return;
    }
    cur++;
  }
}

void trexo_game_config_undo_move(struct trexo_game_config* gc)
{
  int cur = gc->current -1;
  while(cur >= 0){
    if(gc->players[gc->history[cur].turn].type == PLAYER_HUMAN){
      gc->current = cur;
      return;
    }
    cur--;
  }
}

void trexo_game_config_on_ended(const struct trexo_game_config* gc)
{
  printf("%s","Game over!\n");
  const struct game_state* s = trexo_game_config_get_state_const(gc);
  int count[2];
  count[0] = uint64_count(s->turn ? s->discs.opp : s->discs.me);
  count[1] = uint64_count(s->turn ? s->discs.me : s->discs.opp);
  if(count[0] > count[1]){
    printf("Black wins: %d - %d\n",count[0],count[1]);
  }
  else if(count[0] < count[1]){
    printf("White wins: %d - %d\n",count[1],count[0]);
  }
  else{
    printf("Draw: %d - %d\n",count[0],count[1]);
  }
}

struct game_state* trexo_game_config_get_state(struct trexo_game_config* gc)
{
  return &gc->history[gc->current];
}

const struct game_state* trexo_game_config_get_state_const(const struct trexo_game_config* gc)
{
  return &gc->history[gc->current];
}



void trexo_game_config_console_main(struct trexo_game_config* gc)
{
  struct game_state *state,*next;
  
  while(1){
    state = trexo_game_config_get_state(gc);
    if(board_test_game_ended(&state->discs)){
      break;
    }
    next = state + 1;
    struct player* p = gc->players + state->turn;
    trexo_game_config_show_updated_field(gc);
    player_do_move(p,&state->discs,&next->discs);
    gc->current = gc->redo_max = gc->current + 1;
    game_state_update_turn(next);
  }
  trexo_game_config_on_ended(gc);
}


void game_state_print(const struct game_state* gs, FILE* file)
{
  fprintf(file,"%s","+-a-b-c-d-e-f-g-h-+\n");
  int f;
  uint64_t moves,white,black;
  moves = board_get_moves(&gs->discs);
  black = gs->turn ? gs->discs.me : gs->discs.opp;
  white = gs->turn ? gs->discs.opp : gs->discs.me;
  for(f=0;f<64;f++){
    if(f%8 == 0){
      fprintf(file,"%d ",(f/8)+1);
    }
    if(white & (1ull << f)){
      fprintf(file,"%s","\033[31;1m\u2B24\033[0m ");
    }
    else if(black & (1ull << f)){
      fprintf(file,"%s","\033[34;1m\u2B24\033[0m ");
    }
    else if(moves & (1ull << f)){
      fprintf(file,"%s", "- ");
    }  
    else{
      fprintf(file,"%s","  ");
    }
    if(f%8 == 7){
      fprintf(file,"%s","|\n");
    }
  }
  fprintf(file,"%s","+-----------------+\n");
}

void game_state_init(struct game_state* gs)
{
  board_init(&gs->discs);
  gs->turn = 0;
}

void game_state_update_turn(struct game_state* gs)
{
  gs->turn = 1 - gs->turn;
  if(board_has_valid_moves(&gs->discs)){
    return;
  }
  game_state_switch_turn(gs);
  if(board_has_valid_moves(&gs->discs)){
    return;
  }
  game_state_switch_turn(gs); 
}

void game_state_switch_turn(struct game_state* gs)
{
  board_switch_turn(&gs->discs);
  gs->turn = 1 - gs->turn;
}

void trexo_game_config_set_bot(struct trexo_game_config* gc, int colour, int depth, int perfect_depth)
{
  assert(colour==0 || colour==1);
  player_init(&gc->players[colour],gc->bot_type,depth,perfect_depth);
}

struct game_state* game_state_get_children(const struct game_state* gs,struct game_state* out)
{
  struct board children[32];
  struct board* end = board_get_children(&gs->discs,children);
  if(end==children){
    struct game_state copy = *gs;
    game_state_switch_turn(&copy);
    if(board_has_valid_moves(&copy.discs)){
      return game_state_get_children(&copy,out);
    }
    return out;
  }
  struct game_state* out_end = out;
  struct board* it;
  for(it=children;it!=end;it++){
    out_end->discs = *it;
    out_end->turn = 1 - gs->turn;
    out_end++;
  }
  return out_end;
}


