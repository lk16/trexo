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
        trexo_field_init(board->fields + i, 0, board->next_brick_id - 1, 0);
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

            if(
                (left->height != right->height) 
                || (left->height != 0 && left->brick_id == right->brick_id)
            ){
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
            ++output_start;
            ++board->next_brick_id;

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
            ++output_start;
            ++board->next_brick_id;
        }
    }

    // horizontal bricks
    for(r=0; r < TREXO_FIELD_SIDE - 1; ++r){
        for(c=0; c<TREXO_FIELD_SIDE; ++c){
            
            int top_offset = (r * TREXO_FIELD_SIDE) + c;
            int bottom_offset = top_offset + TREXO_FIELD_SIDE;

            top = board->fields + top_offset;   
            bottom = board->fields + bottom_offset;

            if(
                (top->height != bottom->height) 
                || (top->height != 0 && top->brick_id == bottom->brick_id)
            ){
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
            ++output_start;
            ++board->next_brick_id;

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
            ++output_start;
            ++board->next_brick_id;
        }
    }

    *output_end = output_start;
}