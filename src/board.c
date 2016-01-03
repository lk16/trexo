#include "board.h"

void trexo_field_init(
    struct trexo_field *field,
    int height,
    int brick_id,
    int is_x
){
    field->height = height;
    field->brick_id = brick_id;
    field->is_x = is_x;
}

void trexo_board_init(
    struct trexo_board *board
){
    int i;
    board->next_brick_id = 1;
    for(i=0; i<TREXO_NUM_FIELDS; ++i){
        trexo_field_init(
            board->fields + i,
            0,
            board->next_brick_id - 1,
            0
        );
    }
}

void trexo_board_print(
    const struct trexo_board *board
){
    int r,c;
    const struct trexo_field *field; 

    printf("%s","+-");
    for(c=0; c<TREXO_FIELD_SIDE; ++c){
        printf("%s","--");
    }
    printf("%s","+\n");

    for(r=0; r<TREXO_FIELD_SIDE; ++r){
        printf("%s","|");
        for(c=0; c<TREXO_FIELD_SIDE; ++c){
            field = board->fields + (r * TREXO_FIELD_SIDE) + c;
            if(field->height == 0){
                printf("%s"," .");
            }
            else if(field->is_x){
                printf("%s"," x");
            }
            else{
                printf("%s"," o");
            }
        }
        printf("%s"," |\n");
    }

    printf("%s","+-");
    for(c=0; c<TREXO_FIELD_SIDE; ++c){
        printf("%s","--");
    }
    printf("%s","+\n");

#if 0    
    // ---


    printf("%s","\nheights:\n+-");
    for(c=0; c<TREXO_FIELD_SIDE; ++c){
        printf("%s","--");
    }
    printf("%s","+\n");

    for(r=0; r<TREXO_FIELD_SIDE; ++r){
        printf("%s","|");
        for(c=0; c<TREXO_FIELD_SIDE; ++c){
            field = board->fields + (r * TREXO_FIELD_SIDE) + c;
            if(field->height == 0){
                printf("%s","  ");
            }
            else{
                printf(" %d",field->height);
            }
        }
        printf("%s"," |\n");
    }

    printf("%s","+-");
    for(c=0; c<TREXO_FIELD_SIDE; ++c){
        printf("%s","--");
    }
    printf("%s","+\n");

    printf("next_brick_id = %d\n",board->next_brick_id);

    // ---


    printf("%s","\nbrick_ids:\n+-");
    for(c=0; c<TREXO_FIELD_SIDE; ++c){
        printf("%s","--");
    }
    printf("%s","+\n");

    for(r=0; r<TREXO_FIELD_SIDE; ++r){
        printf("%s","|");
        for(c=0; c<TREXO_FIELD_SIDE; ++c){
            field = board->fields + (r * TREXO_FIELD_SIDE) + c;
            if(field->brick_id == 0){
                printf("%s","  ");
            }
            else{
                printf(" %d",field->brick_id);
            }
        }
        printf("%s"," |\n");
    }

    printf("%s","+-");
    for(c=0; c<TREXO_FIELD_SIDE; ++c){
        printf("%s","--");
    }
    printf("%s","+\n");

    printf("next_brick_id = %d\n",board->next_brick_id);


    printf("%s","\n\n=============================\n\n");
#endif
}

void trexo_board_get_children(
    struct trexo_board *board,
    struct trexo_board *output_start,
    struct trexo_board **output_end
){
    int r,c;
    const struct trexo_field *left,*right,*top,*bottom;

    // horizontal bricks
    for(r=0; r<TREXO_FIELD_SIDE; ++r){
        for(c=0; c<TREXO_FIELD_SIDE - 1; ++c){
            
            int left_offset = (r * TREXO_FIELD_SIDE) + c;
            int right_offset = left_offset + 1;

            left = board->fields + left_offset;   
            right = board->fields + right_offset;

            if(!trexo_field_is_valid_move(left,right)){
                continue;
            }



            // O on the left
            *output_start = *board;
            trexo_field_init(
                output_start->fields + left_offset,
                output_start->fields[left_offset].height + 1,
                board->next_brick_id,
                0
            );
            trexo_field_init(
                output_start->fields + right_offset,
                output_start->fields[right_offset].height + 1,
                board->next_brick_id,
                1
            );
            ++output_start->next_brick_id;
            ++output_start;

            // X on the left
            *output_start = *board;
            trexo_field_init(
                output_start->fields + left_offset,
                output_start->fields[left_offset].height + 1,
                board->next_brick_id,
                1
            );
            trexo_field_init(
                output_start->fields + right_offset,
                output_start->fields[right_offset].height + 1,
                board->next_brick_id,
                0
            );
            ++output_start->next_brick_id;
            ++output_start;
        }
    }

    // horizontal bricks
    for(r=0; r < TREXO_FIELD_SIDE - 1; ++r){
        for(c=0; c<TREXO_FIELD_SIDE; ++c){
            
            int top_offset = (r * TREXO_FIELD_SIDE) + c;
            int bottom_offset = top_offset + TREXO_FIELD_SIDE;

            top = board->fields + top_offset;   
            bottom = board->fields + bottom_offset;

            if(!trexo_field_is_valid_move(top,bottom)){
                continue;
            }



            // O on the top
            *output_start = *board;
            trexo_field_init(
                output_start->fields + top_offset,
                output_start->fields[top_offset].height + 1,
                board->next_brick_id,
                0
            );
            trexo_field_init(
                output_start->fields + bottom_offset,
                output_start->fields[bottom_offset].height + 1,
                board->next_brick_id,
                1
            );
            ++output_start->next_brick_id;
            ++output_start;

            // X on the top
            *output_start = *board;
            trexo_field_init(
                output_start->fields + top_offset,
                output_start->fields[top_offset].height + 1,
                board->next_brick_id,
                1
            );
            trexo_field_init(
                output_start->fields + bottom_offset,
                output_start->fields[bottom_offset].height + 1,
                board->next_brick_id,
                0
            );
            ++output_start->next_brick_id;
            ++output_start;
        }
    }

    *output_end = output_start;
}

bool trexo_field_is_valid_move(
    const struct trexo_field *lhs,
    const struct trexo_field *rhs
){
    return ((lhs->brick_id != rhs->brick_id) || (lhs->height == 0)) && (lhs->height == rhs->height);
}




bool trexo_board_is_valid_move_first_half(
    const struct trexo_board *board, 
    int field_index 
){
    (void)board;
    (void)field_index;
    // We just pretend every first half is valid
    // If there is no valid second half, the user will get stuck here and has to undo
    return TRUE;
}

bool trexo_board_is_valid_move_second_half(
    const struct trexo_board *board,
    int first_field_id, 
    int second_field_id 
){
    int row_diff = (first_field_id/TREXO_FIELD_SIDE) - (second_field_id/TREXO_FIELD_SIDE);
    int col_diff = (first_field_id%TREXO_FIELD_SIDE) - (second_field_id%TREXO_FIELD_SIDE);
    row_diff = (row_diff > 0) ? row_diff : -row_diff;
    col_diff = (col_diff > 0) ? col_diff : -col_diff;
    if((col_diff == 1 && row_diff == 0) || (col_diff == 0 && row_diff == 1)){
        return board->fields[second_field_id].height == board->fields[first_field_id].height - 1;
    }
    return 0;
}

int trexo_board_get_unfinished_brick_field_id(
    const struct trexo_board *board
){
    int field_id = -1;
    for(int i=0; i<TREXO_NUM_FIELDS; ++i){
        if(board->fields[i].brick_id == board->next_brick_id){
            if(field_id == -1){
                field_id = i;
            }
            else{
                return -1;
            }
        }
    }
    return field_id;
}

bool trexo_board_try_putting_half_brick(
    struct trexo_board *board,
    int field_index,
    int is_x
){
    int unfinished_id = trexo_board_get_unfinished_brick_field_id(board);
    if(unfinished_id == -1){
        if(!trexo_board_is_valid_move_first_half(board,field_index)){
            return FALSE;
        }
        ++board->fields[field_index].height;
        board->fields[field_index].brick_id = board->next_brick_id;
        board->fields[field_index].is_x = is_x;
    }
    else{
        if(!trexo_board_is_valid_move_second_half(board,unfinished_id,field_index)){
            return FALSE;
        }
        ++board->fields[field_index].height;
        board->fields[field_index].brick_id = board->next_brick_id;
        board->fields[field_index].is_x = !board->fields[unfinished_id].is_x;
        ++board->next_brick_id;
    }
    return TRUE;
}

void trexo_child_generator_init(
    struct trexo_child_generator *gen
){
    gen->next_field_id = 0;
    gen->next_dir = TREXO_MIN_DIR;
}

void trexo_child_generator_advance(
    struct trexo_child_generator *gen
){
    if(gen->next_dir == TREXO_MAX_DIR){
        gen->next_dir = TREXO_MIN_DIR;
        ++gen->next_field_id;
    }
    else{
        ++gen->next_dir;
    }
}

bool trexo_child_generator_next(
    struct trexo_child_generator *gen,
    const struct trexo_board *parent,
    struct trexo_board *child
){
    // x goes in next_field_id
    // o goes in the neighbour determined by next_dir

    if((gen->next_field_id == TREXO_NUM_FIELDS - 1) && (gen->next_dir == TREXO_MAX_DIR)){
        return FALSE;
    }

    bool ok;
    do{
        ok = TRUE;
        switch(gen->next_dir){
            case TREXO_LEFT:
                if(gen->next_field_id % TREXO_FIELD_SIDE == 0){
                    trexo_child_generator_advance(gen);
                    ok = FALSE;
                }
                break;
            case TREXO_RIGHT:
                if(gen->next_field_id % TREXO_FIELD_SIDE == TREXO_FIELD_SIDE - 1){
                    trexo_child_generator_advance(gen);
                    ok = FALSE;
                }
                break;
            case TREXO_UP:
                if(gen->next_field_id / TREXO_FIELD_SIDE == 0){
                    trexo_child_generator_advance(gen);
                    ok = FALSE;
                }            
                break;
            case TREXO_DOWN:
                if(gen->next_field_id / TREXO_FIELD_SIDE == TREXO_FIELD_SIDE - 1){
                    trexo_child_generator_advance(gen);
                    ok = FALSE;
                }
                break;
        }
    }while(!ok);

    *child = *parent;
    
    struct trexo_field *field,*neighbour;

    field = child->fields + gen->next_field_id;
    ++field->height;
    field->brick_id = child->next_brick_id;
    field->is_x = TRUE;

    switch(gen->next_dir){
        case TREXO_LEFT:
            neighbour = field - 1;
            break;
        case TREXO_RIGHT:
            neighbour = field + 1;
            break;
        case TREXO_UP:
            neighbour = field - TREXO_FIELD_SIDE;
            break;
        case TREXO_DOWN:
            neighbour = field + TREXO_FIELD_SIDE;
            break;
    }
    

    ++neighbour->height;
    neighbour->brick_id = child->next_brick_id;
    neighbour->is_x = FALSE;

    ++child->next_brick_id;

    trexo_child_generator_advance(gen);
    return TRUE;
}