/*Auteur: Camil
Job: fonctions concernants l'interaction graphique avec le(s) joueurs
Date:21/02
*/


#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>


int main() {
  int width=660, height=390;
  MLV_Image *image;
  int image_width, image_height;//, text_width, text_height;
  const char* text="Ordinateur Gagne! \n Esc pour retour menu.";

  MLV_create_window( "Player vs Game", "sound", width, height);
  image = MLV_load_image( "assets/images/gameover.jpg" );
  MLV_resize_image_with_proportions(image, width, height);
  MLV_get_image_size(image, &image_width, &image_height);
  MLV_draw_image( image, 0, 0 );
  MLV_get_size_of_text(text, &image_width, &image_height);
  MLV_draw_text(width/3.5, height-90, text, MLV_COLOR_GREEN );


  MLV_actualise_window();
  MLV_wait_seconds(60);
  MLV_free_image( image );
  MLV_free_window();
  return 0;
}
