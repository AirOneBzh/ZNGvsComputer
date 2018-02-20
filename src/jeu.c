#include <stdio.h>
#include <stdlib.h>
#include "../inc/mon_erreur.h"
#include "../inc/allocation.h"
#include "MLV/MLV_all.h"


void jeu(){
  int h=MLV_get_desktop_height();
  int w=MLV_get_desktop_width();
  MLV_create_window("","",w*0.8,h*0.8);
  MLV_wait_seconds(10);
  
  MLV_free_window();
}
