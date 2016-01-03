#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#include <gtk/gtk.h>
#include <glib.h>
#include <glib-object.h>

#include "main_window.h"
#include "board.h"

#include "bitset.h"

int generate_descendants(
    const struct trexo_board *parent,
    int depth
){
    if(depth == 0){
        return 1;
    }
    int total = 0;
    struct trexo_child_generator gen;
    trexo_child_generator_init(&gen);
    struct trexo_board child;
    while(trexo_child_generator_next(&gen,parent,&child)){
        total += generate_descendants(&child,depth-1);
    }
    return total;
}

int main(
	int argc,
	char **argv
){
#if 0
	(void)argc;
    (void)argv;
    //srand(time(NULL));
    struct trexo_main_window window;
    gtk_init(&argc,&argv);
    trexo_main_window_init(&window);  
    //g_timeout_add(100,(GSourceFunc)trexo_game_config_timeout,&window.config);
    gtk_main();
    return 0;
#else
    struct trexo_board board;
    trexo_board_init(&board);
    GTimer *timer = g_timer_new();
    g_timer_start(timer);
    int count = generate_descendants(&board,3);
    g_timer_stop(timer);
    double elapsed = g_timer_elapsed(timer,NULL);
    printf("Took %lf seconds.\n",elapsed);
    printf("Generated %d boards.\n",count);
    printf("Speed: %d boards/sec.\n",(int)(count/elapsed));
    g_timer_destroy(timer);
#endif
}