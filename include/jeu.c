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
#include "mon_erreur.h"
#include "allocation.h"
#include "interface.h"
#include "jeu.h"
#include "MLV/MLV_all.h"

// initialise le tableau d'int à 0 et 4 pions au milieu
void init_pions(int **plateau);

// pose un pion de couleur couleur sur le plateau aux coord x,y
int pose_pion(int couleur, int x, int y, int **plateau);

//avoir la couleur de l'ennemi
int opposant(int couleur);

// lance le jeu avec la fenetre
void jeu(int hauteur,int largeur);

// cap haut bas droit gauche diag...
// verifie si capture

// a_voisin

// coup_valide

// nb_pions

void jeu(int hauteur,int largeur) {
  // int   dh = hauteur_fenetre();
  // int   h  = 0.8 * dh;
  // int   c  = h / 18;
  // int   w  = 16 * h / 9;
  int **plateau;
  int   i;
  int   x, y, joueur = BLANC;
  int   f = 0;

  x       = y = 0;
  plateau = allocation_mem(10, sizeof(int *));

  for (i = 0; i < 10; i++) {
    plateau[i] = allocation_mem_init0(10, sizeof(int));
  }

  // si menu load > tab = fich sinon init_pions
  init_pions(tab);
  // creer fenetre

  creer_fenetre(hauteur,largeur);

  //dess_
  dess_plat();
  dess_apercu_selec(0, 0);
  dess_pions(plateau);
  int r;

  // fin non atteinte
  while (est_fini_partie(joueur,plateau)) {
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
        opposant(jb)
      }
      else {
        // pose_pion(impo)
      }
      break;

      // touche s -> save
      case -2:

      // save(plateau);
      break;

      // save puis Quit
      case -1:

      // save(tab)
      free_jeu();
      exit(0);
    }
    dess_pions(tab);

    #ifdef TEST
    f = 1;
    #endif /* ifdef TEST */
  }
  free_jeu();
}

int opposant(int couleur){
  if(couleur == NOIR)return BLANC;
  return NOIR;
}

void init_pions(int **plateau) {
  int i, j;

  for (i = 1; i <= 8; i++) {
    for (j = 1; j <= 8; j++) {
      plateau[i][j] = VIDE;
    }
  }
  // 4 pions début partie
  // pose_pion()
  plateau[4][4] = plateau[3][3] = BLANC;
  plateau[4][3] = plateau[3][4] = NOIR;
}

// après selection de case verifie si pion peut etre posé
int pose_pion(int couleur, int x, int y, int **plateau) {
  // int i;
  valide=coup_valide(couleur,x,y,plateau);
  if (valide)
  plateau[x][y]=couleur;
  return valide;
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

int cap_diag_bas_droit(int couleur, int i, int j, int **plateau) {
  int i_bis = i + 2, j_bis = j + 2;

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

int cap_diag_bas_gauche(int couleur, int i, int j, int **plateau) {
  int i_bis = i + 2, j_bis = j - 2;

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

int coup_valide(int couleur, int i, int j, int **plateau){
  if(plateau[i][j] != VIDE )return 0;
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
  else return 0;
}

int *nb_pions(int **plateau){
  int i, j, b=0, n=0;
  int blanc_noir[3];
  for(i=1; i<=8; i++)
  for(j=1; j<=8; j++){
    if(plateau[i][j]==BLANC)
    B++;
    if(plateau[i][j]==NOIR)
    N++;
  }
  blanc_noir[0]=b+n;
  blanc_noir[1]=b;
  blanc_noir[2]=n;
  return blanc_noir;
}

int est_fini_partie(int couleur, int **plateau){
  int *etat=nb_pions(plateau);
  int i, j;
  if(etat[0]==64)
  return 1;
  for(i=1; i<=8; i++)
  for(j=1; j<=8; j++)
  if(coup_valide(couleur, i, j, plateau))
  return 0;
  return 1;
}
