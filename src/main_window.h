#pragma once

#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <stdio.h>

#include "game_config.h"
#include "clickable_image.h"



struct trexo_main_window{
  GtkWidget* window;
  GtkWidget* vbox;
  GtkWidget* table;
  struct clickable_image images[8][8];
  struct trexo_game_config config;
};


void trexo_main_window_init(struct trexo_ain_window* mw);
void trexo_main_window_table_init(struct trexo_main_window* mw);

void trexo_main_window_update_fields(struct trexo_main_window* mw,const struct trexo_game_state* gs);
