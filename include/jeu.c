/*
 *   Source JEU_C
 *   Fonctionnalités:
 *   Dessiner le plateau de jeu et gérer les manip du tableau de pions
 *   Auteur: airone@airone-debian (E. LE CORNEC)
 *   Création :04/03/18
 *   MODIFICATION camil les "tab" deviennent "plateau"
 */


#include <stdio.h>
#include <stdlib.h>
#include "../include/mon_erreur.h"
#include "../include/allocation.h"
#include "../include/interface.h"
#include "../include/jeu.h"
#include "MLV/MLV_all.h"

void init_pions(int **plateau);
int  pose_pion(int   j,
               int   x,
               int   y,
               int **plateau);
void retourne_pion_dir(int   x,
                       int   y,
                       int   i,
                       int   dir,
                       int **plateau);
int ligne_pion_dir(int   j,
                   int   x,
                   int   y,
                   int   dir,
                   int **plateau);


void jeu() {
  int   dh = MLV_get_desktop_height();
  int   h  = 0.8 * dh;
  int   c  = h / 18;
  int   w  = 16 * h / 9;
  int **plateau;
  int   i;
  int   x, y, jb = 1, j;
  int   f = 0;

  x   = y = 0;
  plateau = allocation_mem(10, sizeof(int *));

  // menu
  for (i = 0; i < 10; i++) {
    plateau[i] = allocation_mem_init0(10, sizeof(int));
  }

  // si menu load > tab = fich sinon init_pions
  init_pions(tab);
  MLV_create_window("zngOthello", "", w, h);
  dess_plat();
  dess_apercu_selec(0, 0);
  dess_pions(plateau);
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

      if (pose_pion(j, x, y, plateau) == 1) {
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
      plateau[i][j] = VIDE;
    }
  }

  // 4 pions début partie
  plateau[4][4] = plateau[3][3] = BLANC;
  plateau[4][3] = plateau[3][4] = NOIR;
}

// après selection de case verifie si pion peut etre posé
int pose_pion(int j, int x, int y, int **plateau) {
  // int i;

  if ((plateau[x][y] == 0)) {
    plateau[x][y] = j;
    return 1; // pose valide
  }
  else {
    return 1; // pose invalide (pion déjà présent)
  }
}

int cap_haut(int couleur, int i, int j, int **plateau){
    if( i <= 2)
	return 0;
    int i_bis;
    i_bis=i-2;
    while( i_bis != 0 ){
	if( plateau[i_bis][j] == couleur )
	    return 1;
	if( plateau[i_bis][j] == VIDE)
	    return 0;
	else
	    i_bis-=1;
    }
    return 0;
}
    
int cap_bas(int couleur, int i, int j, int **plateau){
    if( i >=7 )
	return 0;
    int i_bis;
    i_bis=i+2;
    while( i_bis != 9 ){
	if( plateau[i_bis][j] == couleur )
	    return 1;
	if( plateau[i_bis][j] == VIDE )
	    return 0;
	else
	    i_bis+=1;
    }
    return 0;
}

int cap_droit(int couleur, int i, int j, int **plateau){
    if( j >=7 )
	return 0;
    int _bis;
    j_bis=j+2;
    while( j_bis != 9 ){
	if( plateau[i][j_bis] == couleur )
	    return 1;
	if( plateau[i][j_bis] == VIDE )
	    return 0;
	else
	    j_bis+=1;
    }
    return 0;
}

int cap_gauche(int couleur, int i, int j, int **plateau){
    if( j <= 2 )
	return 0;
    int j_bis;
    j_bis=j-2;
    while( j_bis != 0 ){
	if( plateau[i][j_bis] == couleur )
	    return 1;
	if( plateau[i][j_bis] == VIDE )
	    return 0;
	else
	    j_bis-=1;
    }
    return 0;
}
    
int cap_diag_haut_droit(int couleur, int i, int j, int **plateau){
    int i_bis=i-2, j_bis=j+2;
    if( j >= || i <=2 )
	return 0;
    while( i_bis != 0 || j_bis != 8){
	if( plateau[i_bis][j_bis] == couleur )
	    return 1;
	if ( plateau[i_bis][j_bis] == VIDE )
	    return 0;
	else{
	    i_bis-=1;
	    j_bis+=1;
	}
    }
    return 0;
}

int cap_diag_haut_gauche(int couleur, int i, int j, int **plateau);
    int i_bis=i-2, j_bis=j-2;
    if( j <= 2 || i <=2 )
	return 0;
    while( i_bis != 0 || j_bis != 0 ){
	if( plateau[i_bis][j_bis] == couleur )
	    return 1;
	if (plateau[i_bis][j_bis] == VIDE )
	    return 0;
	else {
	    i_bis-=1;
	    j_bis-=1;
	}
    }
    return 0;
}


int cap_diag_bas_droit(int couleur, int i, int j, int **plateau);
    int i_bis=i+2, j_bis=j+2;
    if( j >=7 || i >= 7 )
	return 0;
    while( i_bis != 9 || j_bis != 9 ){
	if( plateau[i_bis][j_bis] == couleur )
	    return 1;
	if ( plateau[i_bis][j_bis] == VIDE )
	    return 0;
	else {
	    i_bis+=1;
	    j_bis+=1;
	}
    }
return 0;
}


int cap_diag_bas_gauche(int couleur, int i, int j, int **plateau){
    int i_bis=i+2, j_bis=j-2;
    if( j <=2 || i >= 7 )
	return 0;
    while( i_bis != 9 || j_bis != 0 ){
	if( plateau[i_bis][j_bis] == couleur )
	    return 1;
	if (plateau[i_bis][j_bis] == VIDE )
	    return 0;
	else{
	    i_bis+=1;
	    j_bis-=1;
	}
    }
    return 0;
}

int a_voisin(int i, int j, int **plateau){
    //si on est au bord du plateau
    int vois;
    vois =
	plateau[i-1][j-1]+
	plateau[i-1][j]+
	plateau[i-1][j+1]+
	plateau[i][j-1]+
	plateau[i][j+1]+
	plateau[i+1][j-1]+
	plateau[i+1][j]+
	plateau[i+1][j+1];
    if( vois > 0)
	return 1;
    return 0;
}

int est_legal_coup(int couleur, int i, int j, int **plateau){
    if ( a_voisin(i, j, plateau) )
	return
	    cap_haut( couleur,  i,  j,  plateau) ||
	    cap_bas( couleur,  i,  j,  plateau) ||
	    cap_droit( couleur,  i,  j,  plateau) ||
	    cap_gauche( couleur,  i,  j,  plateau) ||
	    cap_diag_haut_droit( couleur,  i,  j,  plateau) ||
	    cap_diag_haut_gauche( couleur,  i,  j,  plateau) ||
	    cap_diag_bas_droit( couleur,  i,  j,  plateau) ||
	    cap_diag_bas_gauche( couleur,  i,  j,  plateau);
    
}
    

liste coup_possible(int couleur, int **plateau){}
//TODO
