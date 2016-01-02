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

    struct trexo_board board,child;
    trexo_board_init(&board);
    struct trexo_child_generator gen;
    trexo_child_generator_init(&gen);
    while(trexo_child_generator_next(&gen,&board,&child)){
        trexo_board_print(&child);
    }



	/*srand(time(NULL));
    struct trexo_main_window window;
    gtk_init(&argc,&argv);
    trexo_main_window_init(&window);  
    //g_timeout_add(100,(GSourceFunc)trexo_game_config_timeout,&window.config);
    gtk_main();
    return 0;*/  
}