/*
 *   Source JEU_C
 *   Fonctionnalités:
 *   Dessiner le plateau de jeu et gérer les manip du tableau de pions
 *   Auteur: airone@airone-debian (E. LE CORNEC)
 *   Création :04/03/18
 */


#include <stdio.h>
#include <stdlib.h>
#include "../include/mon_erreur.h"
#include "../include/allocation.h"
#include "../include/interface.h"
#include "../include/jeu.h"
#include "MLV/MLV_all.h"

void init_pions(int **tab);
int  pose_pion(int   j,
               int   x,
               int   y,
               int **tab);
void retourne_pion_dir(int   x,
                       int   y,
                       int   i,
                       int   dir,
                       int **tab);
int ligne_pion_dir(int   j,
                   int   x,
                   int   y,
                   int   dir,
                   int **tab);


void jeu() {
  int   dh = MLV_get_desktop_height();
  int   h  = 0.8 * dh;
  int   c  = h / 18;
  int   w  = 16 * h / 9;
  int **tab;
  int   i;
  int   x, y, jb = 1, j;
  int   f = 0;

  x   = y = 0;
  tab = allocation_mem(10, sizeof(int *));

  // menu
  for (i = 0; i < 10; i++) {
    tab[i] = allocation_mem_init0(10, sizeof(int));
  }

  // si menu load > tab = fich sinon init_pions
  init_pions(tab);
  MLV_create_window("zngOthello", "", w, h);
  dess_plat();
  dess_apercu_selec(0, 0);
  dess_pions(tab);
  MLV_actualise_window();
  int r;

  // fin non atteinte
  while (f == 0) {
    j = jb + 1;
    dess_plat();
    r = att_souris_clav(&x, &y);

    // resultat de att souris
    switch (r) {
    // cadre de selection
    case 0:
      dess_apercu_selec(x, y);
      break;

    // clic souris ou entrée
    case 1:

      if (pose_pion(j, x, y, tab) == 1) {
        // jb numero du joueur qui doit jouer 1 ou 2
        jb = 1 - jb;
      }
      else {
        MLV_draw_rectangle(c * (2 * x + 1),
                           c * (2 * y + 1),
                           2 * c,
                           2 * c,
                           MLV_COLOR_RED);
      }
      break;

    // touche s -> save
    case -2:

      // save(tab);
      break;

    // save puis Quit
    case -1:

      // save(tab)
      MLV_free_window();
      exit(0);
    }

    dess_pions(tab);
    MLV_actualise_window();


          #ifdef TEST
    f = 1;
          #endif /* ifdef TEST */
  }
  MLV_free_window();
}

void init_pions(int **tab) {
  int i, j;

  for (i = 1; i <= 8; i++) {
    for (j = 1; j <= 8; j++) {
      tab[i][j] = VIDE;
    }
  }

  // 4 pions début partie
  tab[4][4] = tab[3][3] = BLANC;
  tab[4][3] = tab[3][4] = NOIR;
}

// après selection de case verifie si pion peut etre posé
int pose_pion(int j, int x, int y, int **tab) {
  // int i;

  if ((tab[x][y] == 0)) {
    tab[x][y] = j;
    return 1; // pose valide
  }
  else {
    return 1; // pose invalide (pion déjà présent)
  }
}
