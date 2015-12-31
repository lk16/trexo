#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <glib-object.h>
#include <time.h>

#include "main_window.h"
#include "board.h"



int main(
	int argc,
	char **argv
){
	(void)argc;
	(void)argv;

	struct trexo_board board,children[TREXO_MAX_CHILDREN];
	struct trexo_board *children_end;
	//const struct trexo_board *child_iter;

	trexo_board_init(&board);
	trexo_board_print(&board);

	for(int i=0;i<4;++i){
		trexo_board_get_children(&board,children,&children_end);
		board = *children;
		trexo_board_print(&board);
	}


    /*srand(time(NULL));
    struct trexo_main_window window;
    gtk_init(&argc,&argv);
    trexo_main_window_init(&window);  
    //arg_parse(argc,(const char**)argv,&mw.config);
    //g_timeout_add(100,(GSourceFunc)trexo_game_config_timeout,&window.config);
    gtk_main();
    */
    return 0;  
}