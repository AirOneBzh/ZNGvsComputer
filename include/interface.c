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
    return 0.8*MLV_get_desktop_height ();
}

int largeur_fenetre(){
  return (hauteur_fenetre()*16)/9;
}

void creer_fenetre(int hauteur, int largeur, info infos) {
    MLV_create_window("zngOthello", "", largeur, hauteur);
    dess_plat();
    dess_info(infos);
}

int fin(info i,int gagnant) {
  int h=hauteur_fenetre();
  int w=largeur_fenetre();
  MLV_Image *image;
  int image_width, image_height; // , text_width, text_height;
  const char *text = "Gagne! \n Esc pour retour menu.";
  char *gagnan= gagnant==1?"Joueur 1":"Joueur 2";
  // pour \n dans draw text -> box sinon une seule ligne
  image = MLV_load_image("assets/images/gameover.jpg");
  MLV_resize_image_with_proportions(image, w, h);
  MLV_get_image_size(image, &image_width, &image_height);
  MLV_draw_image(image, 0, 0);
  MLV_get_size_of_text(text, &image_width, &image_height);
  MLV_draw_text(w / 3.5, h - 90, gagnan, MLV_COLOR_GREEN);

  MLV_actualise_window();
  MLV_wait_keyboard(NULL,NULL,NULL);
  MLV_free_image(image);

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
  fprintf(stderr,"GDB1   ");
  int h = hauteur_fenetre();
  fprintf(stderr,"GDB2\n");
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
    int h = hauteur_fenetre();
  int c = h / 18;
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

  int c = hauteur_fenetre()/ 18;
  int kom;
  int nx = 0;
  int ny = 0;

  kom = MLV_wait_keyboard_or_mouse(&key, NULL, NULL, &ny, &nx);

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
    *x = (nx - c) / (2 * c) +1 ;
    *y = (ny - c) / (2 * c) +1 ;
    return 1;
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
  int c = hauteur_fenetre() / 18;
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


void input(char *message,char *in){
  char *input;
  int h=hauteur_fenetre();
  int w=largeur_fenetre();
  MLV_wait_input_box(0.1*w,0.3*h,
		     0.8*w,0.25*h,
		     MLV_COLOR_RED,MLV_COLOR_GREEN,MLV_COLOR_BLACK,
		     message,&input);
  sprintf(in,"%s",input);
}

void creer_fen_menu() {
  int dh = MLV_get_desktop_height();
  int h  = 0.5 * dh;
  int w  = 3 * h / 4;

  MLV_create_window("Menu zngOthello", "2", w, h);
  
}

void clean_fen_menu(){
  MLV_clear_window(MLV_COUL_PLATEAU);
    int h = MLV_get_window_height();
  int w = MLV_get_window_width();
  int c = h * 0.1;
  int t_font = c * 0.8;
   MLV_Font *font2 = MLV_load_font("assets/fonts/DevilBreeze.ttf", t_font);
  MLV_actualise_window();
}

void bouton(float x, char *text) {
  int h = MLV_get_window_height();
  int w = MLV_get_window_width();
  int c = h * 0.1;

  int t_font = c * 0.8;
  MLV_Font *font = MLV_load_font("assets/fonts/pricedown.ttf", t_font);
 

  MLV_draw_filled_rectangle(c, c * (x + 1), w - 2 * c, c, MLV_COLOR_BLACK);
  MLV_draw_filled_rectangle(c, c * (x + 1), w - 2 * c, c, x==8?MLV_COLOR_RED:MLV_COLOR_WHITE);
  MLV_draw_text_with_font(1.5 * c, c * (x + 1), text, font, x==8?MLV_COLOR_GREY:MLV_COLOR_BLACK);
  MLV_actualise_window();
}

int att_souris_menu(int *x) {
  int nx, ny;
  int h=MLV_get_window_height();
  int w=MLV_get_window_width();
  MLV_wait_keyboard_or_mouse(NULL, NULL, NULL, &nx, &ny);
  int xmin=0.135*w;
  int xmax=0.863*w;
  if ((nx > xmin) && (ny < h*0.376) && (nx < xmax) && (ny > h*0.2)) {
    return 1;
  }
  else if((nx > xmin) && (ny < h*0.47) && (nx < xmax) && (ny > h*0.376)){
    return 2;
  }
  else if((nx > xmin) && (ny < h*0.648) && (nx < xmax) && (ny > h*0.55)) {
    return 3;
  }
  else if((nx > xmin) && (ny < h*0.825) && (nx < xmax) && (ny > h*0.725)) {
    return 4;
  }
  else if((nx > xmin) && (nx < xmax) && (ny > h*0.925 )) {
    return 5;
  }
  else{
    fprintf(stderr, "x%d y%d\n", nx, ny);
  }

  return 0;
}
