#include "main_window.h"

void trexo_main_window_init(
    struct trexo_main_window *window
){
    window->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window->window),"Trexo");
    //gtk_window_set_default_size(GTK_WINDOW(window->window),400,400);
    g_signal_connect(window->window,"destroy",G_CALLBACK(gtk_main_quit),NULL);
    window->vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    window->table = gtk_table_new(TREXO_FIELD_SIDE,TREXO_FIELD_SIDE,FALSE);
    trexo_main_window_table_init(window);
    trexo_game_config_init(&window->config,window);
    gtk_box_pack_start(GTK_BOX(window->vbox),window->table,TRUE,0,0);
    gtk_container_add(GTK_CONTAINER(window->window),window->vbox);
    gtk_widget_show_all(window->window);
}

void trexo_main_window_table_init(
    struct trexo_main_window *window
){
    int x,y;
    for(x=0;x<TREXO_FIELD_SIDE;x++){
        for(y=0;y<TREXO_FIELD_SIDE;y++){
            clickable_image_init(
                &window->images[x][y],
                "./images/default/empty.png",
                y*TREXO_FIELD_SIDE+x,
                &window->config
            );
            gtk_table_attach(
                GTK_TABLE(window->table),
                window->images[x][y].ebox,
                x,x+1,
                y,y+1,
                GTK_SHRINK,GTK_SHRINK,
                0,
                0
            );
        }
    }
}


void trexo_main_window_update_fields(
    struct trexo_main_window *window,
    const struct trexo_board *board
){
    (void)window;
    (void)board;
    /*
      const char* imagefile;
      uint64_t black = (state->turn ? gs->discs.opp : gs->discs.me);
      uint64_t white = (gs->turn ? gs->discs.me : gs->discs.opp);
      
      
      int i;
      for(i=0;i<64;i++){
        if(white & uint64_set[i]){
          imagefile = "./images/white.png";
        }
        else if(black & uint64_set[i]){
          imagefile = "./images/black.png";
        }
        else if(board_is_valid_move(&gs->discs,i)){
          if(gs->turn){
            imagefile = "./images/move_white.png";
          }
          else{
            imagefile = "./images/move_black.png";
          }
        }
        else{
          imagefile = "./images/empty.png";
        }
        GtkWidget* im = mw->images[i%8][i/8].image;
        gtk_image_set_from_file(GTK_IMAGE(im),imagefile);
      }
    */
}



