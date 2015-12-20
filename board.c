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

	printf("%s","+---------------------+\n");

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


	printf("%s","+---------------------+\n");
}