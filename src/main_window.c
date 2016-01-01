#include "main_window.h"

void trexo_main_window_init(
    struct trexo_main_window *window
){
    window->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window->window),"Trexo");
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
    char imagefile[80];
    const struct trexo_field *field;

    char xo;

    for(int i=0; i<TREXO_NUM_FIELDS; i++){
        strncpy(imagefile,TREXO_IMAGE_PATH,sizeof(imagefile));
        field = board->fields + i;
        if(field->height == 0){
            snprintf(imagefile,sizeof(imagefile),"%s/empty.png",TREXO_IMAGE_PATH);
        }
        else{
            xo = field->is_x ? 'x' : 'o';

            if((i % TREXO_FIELD_SIDE > 0) && field->brick_id == board->fields[i-1].brick_id){
                snprintf(imagefile,sizeof(imagefile),"%s/%c_left.png",TREXO_IMAGE_PATH,xo);    
            }
            else if((i % TREXO_FIELD_SIDE < (TREXO_FIELD_SIDE - 1)) && field->brick_id == board->fields[i+1].brick_id){
                snprintf(imagefile,sizeof(imagefile),"%s/%c_right.png",TREXO_IMAGE_PATH,xo);    
            }
            else if((i / TREXO_FIELD_SIDE > 0) && field->brick_id == board->fields[i - TREXO_NUM_FIELDS].brick_id){
                snprintf(imagefile,sizeof(imagefile),"%s/%c_up.png",TREXO_IMAGE_PATH,xo);    
            }
            else if((i / TREXO_FIELD_SIDE < (TREXO_FIELD_SIDE - 1)) && field->brick_id == board->fields[i + TREXO_NUM_FIELDS].brick_id){
                snprintf(imagefile,sizeof(imagefile),"%s/%c_down.png",TREXO_IMAGE_PATH,xo);    
            }
            else{
                snprintf(imagefile,sizeof(imagefile),"%s/%c_neutral.png",TREXO_IMAGE_PATH,xo);        
            }
        }
        GtkWidget* im = window->images[i % TREXO_FIELD_SIDE][i / TREXO_FIELD_SIDE].image;
        gtk_image_set_from_file(GTK_IMAGE(im),imagefile);
      }
}



