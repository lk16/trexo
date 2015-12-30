#include "board.h"

#include <stdio.h>

int main();

int main(){

	struct trexo_board board;
	trexo_board_init(&board);

	struct trexo_board children[TREXO_MAX_CHILDREN];
	struct trexo_board *child_end;


	trexo_board_get_children(&board,children,&child_end);

	board = children[0];

	trexo_board_get_children(&board,children,&child_end);

	struct trexo_board *child_iter = children;

	while(child_iter != child_end){
		trexo_board_print(child_iter);
		++child_iter;
	}

	printf("There are %ld children.\n",child_end - children);


	return 0;
}