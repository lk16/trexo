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
    gen->move_id = 0;
}

void trexo_child_generator_advance(
    struct trexo_child_generator *gen
){
    ++gen->move_id;
}

bool trexo_child_generator_next(
    struct trexo_child_generator *gen,
    const struct trexo_board *parent,
    struct trexo_board *child
){
    // x goes in next_field_id
    // o goes in the neighbour determined by next_dir

    const int direction_diff[4] = { 
        -1,
        1,
        -TREXO_FIELD_SIDE,
        TREXO_FIELD_SIDE 
    };

    const struct trexo_move *move = trexo_moves + gen->move_id;


    int field_id = move->field_id;
    int neighbour_id = field_id + direction_diff[move->direction];

    if(gen->move_id == 0){
        *child = *parent;
    }
    else{
        const struct trexo_move *prev_move = move - 1;
        int prev_field_ids[2] = {
            prev_move->field_id,
            prev_move->field_id + direction_diff[prev_move->direction]
        };
        for(int i=0; i<2; ++i){
            child->fields[prev_field_ids[i]] = parent->fields[prev_field_ids[i]];
        }
    }

    const struct trexo_field *a,*b;
    a = parent->fields + field_id;
    b = parent->fields + neighbour_id;

    do{
        if(a->height != b->height){
            trexo_child_generator_advance(gen);
            continue;
        }
        if((a->brick_id != b->brick_id) && (a->height != 0)){
            trexo_child_generator_advance(gen);
            continue;
        }
    }while(FALSE);

    if(gen->move_id == TREXO_MAX_CHILDREN){
        return FALSE;
    }

    ++child->fields[field_id].height;
    child->fields[field_id].brick_id = child->next_brick_id;
    child->fields[field_id].is_x = TRUE;
 
    ++child->fields[neighbour_id].height;
    child->fields[neighbour_id].brick_id = child->next_brick_id;
    child->fields[neighbour_id].is_x = TRUE;

    trexo_child_generator_advance(gen);
    return TRUE;
}

const struct trexo_move trexo_moves[TREXO_MAX_CHILDREN] = {
    {0,TREXO_RIGHT},
    {0,TREXO_DOWN},
    {1,TREXO_LEFT},
    {1,TREXO_RIGHT},
    {1,TREXO_DOWN},
    {2,TREXO_LEFT},
    {2,TREXO_RIGHT},
    {2,TREXO_DOWN},
    {3,TREXO_LEFT},
    {3,TREXO_RIGHT},
    {3,TREXO_DOWN},
    {4,TREXO_LEFT},
    {4,TREXO_RIGHT},
    {4,TREXO_DOWN},
    {5,TREXO_LEFT},
    {5,TREXO_RIGHT},
    {5,TREXO_DOWN},
    {6,TREXO_LEFT},
    {6,TREXO_RIGHT},
    {6,TREXO_DOWN},
    {7,TREXO_LEFT},
    {7,TREXO_RIGHT},
    {7,TREXO_DOWN},
    {8,TREXO_LEFT},
    {8,TREXO_RIGHT},
    {8,TREXO_DOWN},
    {9,TREXO_LEFT},
    {9,TREXO_DOWN},
    {10,TREXO_RIGHT},
    {10,TREXO_UP},
    {10,TREXO_DOWN},
    {11,TREXO_LEFT},
    {11,TREXO_RIGHT},
    {11,TREXO_UP},
    {11,TREXO_DOWN},
    {12,TREXO_LEFT},
    {12,TREXO_RIGHT},
    {12,TREXO_UP},
    {12,TREXO_DOWN},
    {13,TREXO_LEFT},
    {13,TREXO_RIGHT},
    {13,TREXO_UP},
    {13,TREXO_DOWN},
    {14,TREXO_LEFT},
    {14,TREXO_RIGHT},
    {14,TREXO_UP},
    {14,TREXO_DOWN},
    {15,TREXO_LEFT},
    {15,TREXO_RIGHT},
    {15,TREXO_UP},
    {15,TREXO_DOWN},
    {16,TREXO_LEFT},
    {16,TREXO_RIGHT},
    {16,TREXO_UP},
    {16,TREXO_DOWN},
    {17,TREXO_LEFT},
    {17,TREXO_RIGHT},
    {17,TREXO_UP},
    {17,TREXO_DOWN},
    {18,TREXO_LEFT},
    {18,TREXO_RIGHT},
    {18,TREXO_UP},
    {18,TREXO_DOWN},
    {19,TREXO_LEFT},
    {19,TREXO_UP},
    {19,TREXO_DOWN},
    {20,TREXO_RIGHT},
    {20,TREXO_UP},
    {20,TREXO_DOWN},
    {21,TREXO_LEFT},
    {21,TREXO_RIGHT},
    {21,TREXO_UP},
    {21,TREXO_DOWN},
    {22,TREXO_LEFT},
    {22,TREXO_RIGHT},
    {22,TREXO_UP},
    {22,TREXO_DOWN},
    {23,TREXO_LEFT},
    {23,TREXO_RIGHT},
    {23,TREXO_UP},
    {23,TREXO_DOWN},
    {24,TREXO_LEFT},
    {24,TREXO_RIGHT},
    {24,TREXO_UP},
    {24,TREXO_DOWN},
    {25,TREXO_LEFT},
    {25,TREXO_RIGHT},
    {25,TREXO_UP},
    {25,TREXO_DOWN},
    {26,TREXO_LEFT},
    {26,TREXO_RIGHT},
    {26,TREXO_UP},
    {26,TREXO_DOWN},
    {27,TREXO_LEFT},
    {27,TREXO_RIGHT},
    {27,TREXO_UP},
    {27,TREXO_DOWN},
    {28,TREXO_LEFT},
    {28,TREXO_RIGHT},
    {28,TREXO_UP},
    {28,TREXO_DOWN},
    {29,TREXO_LEFT},
    {29,TREXO_UP},
    {29,TREXO_DOWN},
    {30,TREXO_RIGHT},
    {30,TREXO_UP},
    {30,TREXO_DOWN},
    {31,TREXO_LEFT},
    {31,TREXO_RIGHT},
    {31,TREXO_UP},
    {31,TREXO_DOWN},
    {32,TREXO_LEFT},
    {32,TREXO_RIGHT},
    {32,TREXO_UP},
    {32,TREXO_DOWN},
    {33,TREXO_LEFT},
    {33,TREXO_RIGHT},
    {33,TREXO_UP},
    {33,TREXO_DOWN},
    {34,TREXO_LEFT},
    {34,TREXO_RIGHT},
    {34,TREXO_UP},
    {34,TREXO_DOWN},
    {35,TREXO_LEFT},
    {35,TREXO_RIGHT},
    {35,TREXO_UP},
    {35,TREXO_DOWN},
    {36,TREXO_LEFT},
    {36,TREXO_RIGHT},
    {36,TREXO_UP},
    {36,TREXO_DOWN},
    {37,TREXO_LEFT},
    {37,TREXO_RIGHT},
    {37,TREXO_UP},
    {37,TREXO_DOWN},
    {38,TREXO_LEFT},
    {38,TREXO_RIGHT},
    {38,TREXO_UP},
    {38,TREXO_DOWN},
    {39,TREXO_LEFT},
    {39,TREXO_UP},
    {39,TREXO_DOWN},
    {40,TREXO_RIGHT},
    {40,TREXO_UP},
    {40,TREXO_DOWN},
    {41,TREXO_LEFT},
    {41,TREXO_RIGHT},
    {41,TREXO_UP},
    {41,TREXO_DOWN},
    {42,TREXO_LEFT},
    {42,TREXO_RIGHT},
    {42,TREXO_UP},
    {42,TREXO_DOWN},
    {43,TREXO_LEFT},
    {43,TREXO_RIGHT},
    {43,TREXO_UP},
    {43,TREXO_DOWN},
    {44,TREXO_LEFT},
    {44,TREXO_RIGHT},
    {44,TREXO_UP},
    {44,TREXO_DOWN},
    {45,TREXO_LEFT},
    {45,TREXO_RIGHT},
    {45,TREXO_UP},
    {45,TREXO_DOWN},
    {46,TREXO_LEFT},
    {46,TREXO_RIGHT},
    {46,TREXO_UP},
    {46,TREXO_DOWN},
    {47,TREXO_LEFT},
    {47,TREXO_RIGHT},
    {47,TREXO_UP},
    {47,TREXO_DOWN},
    {48,TREXO_LEFT},
    {48,TREXO_RIGHT},
    {48,TREXO_UP},
    {48,TREXO_DOWN},
    {49,TREXO_LEFT},
    {49,TREXO_UP},
    {49,TREXO_DOWN},
    {50,TREXO_RIGHT},
    {50,TREXO_UP},
    {50,TREXO_DOWN},
    {51,TREXO_LEFT},
    {51,TREXO_RIGHT},
    {51,TREXO_UP},
    {51,TREXO_DOWN},
    {52,TREXO_LEFT},
    {52,TREXO_RIGHT},
    {52,TREXO_UP},
    {52,TREXO_DOWN},
    {53,TREXO_LEFT},
    {53,TREXO_RIGHT},
    {53,TREXO_UP},
    {53,TREXO_DOWN},
    {54,TREXO_LEFT},
    {54,TREXO_RIGHT},
    {54,TREXO_UP},
    {54,TREXO_DOWN},
    {55,TREXO_LEFT},
    {55,TREXO_RIGHT},
    {55,TREXO_UP},
    {55,TREXO_DOWN},
    {56,TREXO_LEFT},
    {56,TREXO_RIGHT},
    {56,TREXO_UP},
    {56,TREXO_DOWN},
    {57,TREXO_LEFT},
    {57,TREXO_RIGHT},
    {57,TREXO_UP},
    {57,TREXO_DOWN},
    {58,TREXO_LEFT},
    {58,TREXO_RIGHT},
    {58,TREXO_UP},
    {58,TREXO_DOWN},
    {59,TREXO_LEFT},
    {59,TREXO_UP},
    {59,TREXO_DOWN},
    {60,TREXO_RIGHT},
    {60,TREXO_UP},
    {60,TREXO_DOWN},
    {61,TREXO_LEFT},
    {61,TREXO_RIGHT},
    {61,TREXO_UP},
    {61,TREXO_DOWN},
    {62,TREXO_LEFT},
    {62,TREXO_RIGHT},
    {62,TREXO_UP},
    {62,TREXO_DOWN},
    {63,TREXO_LEFT},
    {63,TREXO_RIGHT},
    {63,TREXO_UP},
    {63,TREXO_DOWN},
    {64,TREXO_LEFT},
    {64,TREXO_RIGHT},
    {64,TREXO_UP},
    {64,TREXO_DOWN},
    {65,TREXO_LEFT},
    {65,TREXO_RIGHT},
    {65,TREXO_UP},
    {65,TREXO_DOWN},
    {66,TREXO_LEFT},
    {66,TREXO_RIGHT},
    {66,TREXO_UP},
    {66,TREXO_DOWN},
    {67,TREXO_LEFT},
    {67,TREXO_RIGHT},
    {67,TREXO_UP},
    {67,TREXO_DOWN},
    {68,TREXO_LEFT},
    {68,TREXO_RIGHT},
    {68,TREXO_UP},
    {68,TREXO_DOWN},
    {69,TREXO_LEFT},
    {69,TREXO_UP},
    {69,TREXO_DOWN},
    {70,TREXO_RIGHT},
    {70,TREXO_UP},
    {70,TREXO_DOWN},
    {71,TREXO_LEFT},
    {71,TREXO_RIGHT},
    {71,TREXO_UP},
    {71,TREXO_DOWN},
    {72,TREXO_LEFT},
    {72,TREXO_RIGHT},
    {72,TREXO_UP},
    {72,TREXO_DOWN},
    {73,TREXO_LEFT},
    {73,TREXO_RIGHT},
    {73,TREXO_UP},
    {73,TREXO_DOWN},
    {74,TREXO_LEFT},
    {74,TREXO_RIGHT},
    {74,TREXO_UP},
    {74,TREXO_DOWN},
    {75,TREXO_LEFT},
    {75,TREXO_RIGHT},
    {75,TREXO_UP},
    {75,TREXO_DOWN},
    {76,TREXO_LEFT},
    {76,TREXO_RIGHT},
    {76,TREXO_UP},
    {76,TREXO_DOWN},
    {77,TREXO_LEFT},
    {77,TREXO_RIGHT},
    {77,TREXO_UP},
    {77,TREXO_DOWN},
    {78,TREXO_LEFT},
    {78,TREXO_RIGHT},
    {78,TREXO_UP},
    {78,TREXO_DOWN},
    {79,TREXO_LEFT},
    {79,TREXO_UP},
    {79,TREXO_DOWN},
    {80,TREXO_RIGHT},
    {80,TREXO_UP},
    {80,TREXO_DOWN},
    {81,TREXO_LEFT},
    {81,TREXO_RIGHT},
    {81,TREXO_UP},
    {81,TREXO_DOWN},
    {82,TREXO_LEFT},
    {82,TREXO_RIGHT},
    {82,TREXO_UP},
    {82,TREXO_DOWN},
    {83,TREXO_LEFT},
    {83,TREXO_RIGHT},
    {83,TREXO_UP},
    {83,TREXO_DOWN},
    {84,TREXO_LEFT},
    {84,TREXO_RIGHT},
    {84,TREXO_UP},
    {84,TREXO_DOWN},
    {85,TREXO_LEFT},
    {85,TREXO_RIGHT},
    {85,TREXO_UP},
    {85,TREXO_DOWN},
    {86,TREXO_LEFT},
    {86,TREXO_RIGHT},
    {86,TREXO_UP},
    {86,TREXO_DOWN},
    {87,TREXO_LEFT},
    {87,TREXO_RIGHT},
    {87,TREXO_UP},
    {87,TREXO_DOWN},
    {88,TREXO_LEFT},
    {88,TREXO_RIGHT},
    {88,TREXO_UP},
    {88,TREXO_DOWN},
    {89,TREXO_LEFT},
    {89,TREXO_UP},
    {89,TREXO_DOWN},
    {90,TREXO_RIGHT},
    {90,TREXO_UP},
    {91,TREXO_LEFT},
    {91,TREXO_RIGHT},
    {91,TREXO_UP},
    {92,TREXO_LEFT},
    {92,TREXO_RIGHT},
    {92,TREXO_UP},
    {93,TREXO_LEFT},
    {93,TREXO_RIGHT},
    {93,TREXO_UP},
    {94,TREXO_LEFT},
    {94,TREXO_RIGHT},
    {94,TREXO_UP},
    {95,TREXO_LEFT},
    {95,TREXO_RIGHT},
    {95,TREXO_UP},
    {96,TREXO_LEFT},
    {96,TREXO_RIGHT},
    {96,TREXO_UP},
    {97,TREXO_LEFT},
    {97,TREXO_RIGHT},
    {97,TREXO_UP},
    {98,TREXO_LEFT},
    {98,TREXO_RIGHT},
    {98,TREXO_UP},
    {99,TREXO_LEFT},
    {99,TREXO_UP}
};