#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <glib-object.h>
#include <time.h>

#include "main_window.h"
#include "board.h"

#include "bitset.h"


int main(
	int argc,
	char **argv
){
	/*srand(time(NULL));
    struct trexo_main_window window;
    gtk_init(&argc,&argv);
    trexo_main_window_init(&window);  
    //g_timeout_add(100,(GSourceFunc)trexo_game_config_timeout,&window.config);
    gtk_main();
    */  
    (void)argc;
    (void)argv;


    struct bits235 x;
    bits235_init(&x);
    bits235_print(&x);




    /*
    uint64_t b = 0xff;
    assert(uint64_first_index(b) == 0);
    assert(uint64_first_bit(b) == 0x1);
    assert(uint64_count(b) == 8);
    */
    return 0;
}