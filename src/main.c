#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <glib-object.h>
#include <time.h>

#include "main_window.h"
#include "board.h"



int main(int argc,char** argv){
    srand(time(NULL));
    struct trexo_main_window window;
    gtk_init(&argc,&argv);
    trexo_main_window_init(&window);  
    //arg_parse(argc,(const char**)argv,&mw.config);
    //g_timeout_add(100,(GSourceFunc)trexo_game_config_timeout,&window.config);
    gtk_main();
    return 0;  
}