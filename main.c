#include "board.h"

#include <stdio.h>

int main(){

	struct trexo_board board;
	trexo_board_init(&board);
	trexo_board_print(&board);

	return 0;
}