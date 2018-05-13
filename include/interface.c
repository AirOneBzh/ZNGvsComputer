/*
 *   Source INTER_C
 *   Fonctionnalités:
 *   Fonctions concernant l'interaction graphique avec le/s joueurs
 *   Auteurs: airone@airone-debian (E. LE CORNEC) et Camil BRAHMI
 *   Création : 21/02
 *
 *   Historique:   - adaptation en module pour intégration à la fin du jeu
 *                 - ajout des fonctions dess plateau + pions
 *                 - ajout de l'interaction souris
 */


#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "interface.h"
#include "jeu.h"

#define MLV_COUL_PLATEAU MLV_rgba(1, 105, 56, 255)


void dess_info(info i);

int  hauteur_fenetre() {
    return 0.8*MLV_get_desktop_height();
}

int largeur_fenetre(){
  return (hauteur_fenetre()*16)/9;
}

void creer_fenetre(int hauteur, int largeur, info infos) {
    MLV_create_window("zngOthello", "", largeur, hauteur);
    dess_plat();
    dess_info(infos);
}

int fin() {
  MLV_create_window("","",largeur_fenetre(),hauteur_fenetre());
  int h =100;
  int w=90;
  MLV_Image *image;
  int image_width, image_height; // , text_width, text_height;
  const char *text = "Ordinateur Gagne! \n Esc pour retour menu.";

  // pour \n dans draw text -> box sinon une seule ligne
  image = MLV_load_image("assets/images/gameover.jpg");
  MLV_resize_image_with_proportions(image, w, h);
  MLV_get_image_size(image, &image_width, &image_height);
  MLV_draw_image(image, 0, 0);
  MLV_get_size_of_text(text, &image_width, &image_height);
  MLV_draw_text(w / 3.5, h - 90, text, MLV_COLOR_GREEN);


  MLV_actualise_window();
  MLV_wait_seconds(60);
  MLV_free_image(image);
  MLV_free_window();
  return 0;
}

// Dessine le plateau vide
void dess_plat() {
  int h = hauteur_fenetre();
  int c = h / 18;
  int i;

  MLV_draw_filled_rectangle(0, 0, h, h, MLV_COUL_PLATEAU);

  // MLV_clear_window(MLV_rgba(100, 200, 150, 100));
  MLV_draw_rectangle(c, c, 16 * c, 16 * c, MLV_COLOR_WHITE);

  for (i = 1; i < 8; i++) {
    MLV_draw_line(c + c * 2 * i,
                  c,
                  c + c * 2 * i,
                  c * 17 - 2,
                  MLV_COLOR_WHITE);
    MLV_draw_line(c,
                  c + c * 2 * i,
                  c * 17 - 2,
                  c + c * 2 * i,
                  MLV_COLOR_WHITE);
  }
  MLV_actualise_window();
}

void dess_info(info i) {
  int h=hauteur_fenetre();
  int w=largeur_fenetre();
  int c = h * 0.1;
  char pion_1[5],pion_2[5],pion_t[5];
  int t_font = c * 0.8;
  sprintf(pion_1,"%d",i.nb_pions[1]);
  sprintf(pion_2,"%d",i.nb_pions[2]);
  sprintf(pion_t,"%d",i.nb_pions[0]);
  MLV_Font *font = MLV_load_font("assets/fonts/pricedown.ttf", t_font);
  fprintf(stderr,"hauteur %d largeur %d ",h,w);
  MLV_draw_filled_rectangle(h, 0.5, 7*h/9, h, MLV_COUL_PLATEAU);
  MLV_draw_text_with_font(1.1*h,0.2*h,"zngOthello",font,MLV_rgba(177,86,149,255));
  MLV_draw_text_with_font(1.1*h,0.3*h,i.joueur_1,font,MLV_COLOR_BLACK);
  MLV_draw_text_with_font(1.1*h,0.4*h,i.joueur_2,font,MLV_COLOR_WHITE);
  MLV_draw_text_with_font(1.1*h,0.5*h,"Plateau",font,MLV_rgba(177,86,149,255));
  
  MLV_draw_text_with_font(1.5*h,0.3*h,pion_1,font,MLV_COLOR_BLACK);
  MLV_draw_text_with_font(1.5*h,0.4*h,pion_2,font,MLV_COLOR_WHITE);
  MLV_draw_text_with_font(1.5*h,0.5*h,pion_t,font,MLV_rgba(177,86,149,255));
  
  MLV_actualise_window();
  // 
}

void free_jeu() {
  MLV_free_window();
}

// Dessine les pions tels que disposés dans tab([8][8])
void dess_pions(int **tab) {
  int i, j;
  int h = MLV_get_window_height();
  int c = h / 18;

  for (j = 1; j <= 8; j++) {
    for (i = 1; i <= 8; i++) {
      if (tab[j][i] == BLANC) {
        MLV_draw_filled_circle((i * 2) * c, (j * 2) * c, 0.8 * c,
                               MLV_COLOR_WHITE);
        MLV_draw_filled_circle((i * 2) * c, (j * 2) * c, 0.7 * c,
                               MLV_COLOR_BLACK);
        MLV_draw_filled_circle((i * 2) * c, (j * 2) * c, 0.6 * c,
                               MLV_COLOR_WHITE);
      }

      if (tab[j][i] == NOIR) {
        MLV_draw_filled_circle((i * 2) * c, (j * 2) * c, 0.8 * c,
                               MLV_COLOR_BLACK);
        MLV_draw_filled_circle((i * 2) * c, (j * 2) * c, 0.7 * c,
                               MLV_COLOR_WHITE);
        MLV_draw_filled_circle((i * 2) * c, (j * 2) * c, 0.6 * c,
                               MLV_COLOR_BLACK);
      }
    }
  }
  MLV_actualise_window();
}

void pose_pion_fail(int x, int y) {
  int c = MLV_get_window_height() / 18;
  fprintf(stderr,"aprercu %d %d\n",x,y);
  if(x<8 && x>=0 && y<8 && y>=0){
  MLV_draw_rectangle(c * (2 * x + 1),
                     c * (2 * y + 1),
                     1.8 * c,
                     1.8 * c,
                     MLV_COLOR_RED);
  MLV_actualise_window();
  }
}

int att_souris_clav(int *x, int *y) {
  MLV_Keyboard_button key;

  int c = MLV_get_window_height() / 18;
  int kom;
  int nx = 0;
  int ny = 0;

  kom = MLV_wait_keyboard_or_mouse(&key, NULL, NULL, &nx, &ny);

  if (kom == MLV_KEY) {
    switch (key) {
    case MLV_KEYBOARD_UP:
      (*y)--;
      break;

    case MLV_KEYBOARD_DOWN:
      (*y)++;
      break;

    case MLV_KEYBOARD_RIGHT:
      (*x)++;
      break;

    case MLV_KEYBOARD_LEFT:
      (*x)--;
      break;

    case MLV_KEYBOARD_RETURN:
      return 1;

      break;

    case MLV_KEYBOARD_q:
    case MLV_KEYBOARD_ESCAPE:
      return -1;

    case MLV_KEYBOARD_s:
      return -2;

    default:
      break;
    }
  }
  else if (kom == MLV_MOUSE_BUTTON) {
    *x = (nx - c) / (2 * c);
    *y = (ny - c) / (2 * c);
  }
  else {
    fprintf(stderr, "wait_keyboard_or_mouse renvoi autre chose que key ou mouse");
  }

  return 0;
}

/*
   q sauvegarde et quitte
   s sauvegarde
   f fullscreen
   echap menu
   entrer = selection
 */

// Carré de couleur selection clavier
void dess_apercu_selec(int x, int y) {
  int c = MLV_get_window_height() / 18;
  fprintf(stderr,"aprercu %d %d\n",x,y);
  if(x<8 && x>=0 && y<8 && y>=0){
  MLV_draw_rectangle(c * (2 * x + 1),
                     c * (2 * y + 1),
                     1.8 * c,
                     1.8 * c,
                     MLV_COLOR_BLACK);
  MLV_actualise_window();
  }
}

/******************/
/* Interface Menu */
/******************/

int input_char(char *c){
  int h=MLV_get_window_height();
  int w=MLV_get_window_width();
  char *input;
  MLV_wait_input_box(0.1*w,0.3*h,
		     0.8*w,0.25*h,
		     MLV_COLOR_RED,MLV_COLOR_GREEN,MLV_COLOR_BLACK,
		     "      Nom joueur   ",&input);
  strcpy(c,input);
  
  return 1;
}

int input_int(int *x){
  int h=MLV_get_window_height();
  int w=MLV_get_window_width();
  char *input;
  int i;
  MLV_wait_input_box(0.1*w,0.3*h,
		     0.8*w,0.25*h,
		     MLV_COLOR_RED,MLV_COLOR_GREEN,MLV_COLOR_BLACK,
		     "     Joueur (-1) IA (niv (0->4)   ",&input);
  for(i=0;i<strlen(input);i++){
    if(!isdigit(input[i]))
      return 0;
  }
  *x=atoi(input);
  return 1;
}

void creer_fen_menu() {
  int dh = MLV_get_desktop_height();
  int h  = 0.5 * dh;
  int w  = 3 * h / 4;

  MLV_create_window("Menu zngOthello", "2", w, h);
  
}

void clean_fen_menu(){
  MLV_clear_window(MLV_COUL_PLATEAU);
  MLV_actualise_window();
}

void bouton(float x, char *text) {
  int h = MLV_get_window_height();
  int w = MLV_get_window_width();
  int c = h * 0.1;

  int t_font = c * 0.8;

  MLV_Font *font = MLV_load_font("assets/fonts/pricedown.ttf", t_font);

  MLV_draw_filled_rectangle(c, c * (x + 1), w - 2 * c, c, MLV_COLOR_BLACK);
  MLV_draw_filled_rectangle(c, c * (x + 1), w - 2 * c, c, MLV_COLOR_WHITE);
  MLV_draw_text_with_font(1.5 * c, c * (x + 1), text, font, MLV_COLOR_BLACK);
  MLV_actualise_window();
}

int att_souris_menu(int *x) {
  int nx, ny;
  
  MLV_wait_keyboard_or_mouse(NULL, NULL, NULL, &nx, &ny);

  if ((nx < 466) && (ny < 217) && (nx > 73) && (ny > 145)) {
    return 1;
  }
  else if((nx < 466) && (ny < 339) && (nx > 73) && (ny > 271)){
    return 2;
  }
  else if((nx < 466) && (ny < 467) && (nx > 73) && (ny > 396)) {
    return 3;
  }
  else if((nx < 466) && (ny < 594) && (nx > 73) && (ny > 522)) {
    return 4;
  }
   else if((nx < 466) && (nx > 73) && (ny > 594)) {
    return 5;
  }
  else{
    fprintf(stderr, "x%d y%d\n", nx, ny);
  }

  return 0;
}
