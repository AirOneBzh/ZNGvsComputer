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
#include "IA.h"

int jouer_coup_joueur(int joueur, int **plateau) {
  int r;
  int x = 0, y = 0;
  int valide=0;
  while(valide==0 ){
    r = att_souris_clav(&x, &y);

    if (r == 1) {
      valide=pose_pion(joueur, x, y, plateau);
    }
    if(r==-1)
      valide=-1;
  }
  return r;

  // resultat de att souris
}

int jeu(int hauteur, int largeur, info infos) {
  // int   dh = hauteur_fenetre();
  // int   h  = 0.8 * dh;
  // int   c  = h / 18;
  // int   w  = 16 * h / 9;
  int **plateau;
  int   i;
  int   joueur = NOIR;
  int   tour = infos.niv1;
  int   prof;

  // J1 NOIR
  // J2 BLANC
 
  plateau = allocation_mem(10, sizeof(int *));

  for (i = 0; i < 10; i++) {
    plateau[i] = allocation_mem_init0(10, sizeof(int));
  }

  // si menu load > tab = fich sinon init_pions
  init_pions(plateau);
  infos.nb_pions = nb_pions(plateau);

  // creer fenetre
  creer_fenetre(hauteur, largeur, infos);


  int r;

  // fin non atteinte
  //  !est_fini_partie(joueur,plateau)
  while (!est_fini_partie(joueur,plateau)) {
    dess_plat();
    infos.nb_pions=nb_pions(plateau);
    dess_info(infos);
    dess_pions(plateau);


    switch (tour) {
    /* TODO */
    case -10:
	r = jouer_coup_joueur(joueur, plateau);

      if (r == -1) {
        return 1;
      }
      break;

    case 0:
      attente(1);
      jouer_coup_niveau0(joueur, plateau);
      break;

    case 10:
      attente(1);
      jouer_coup_niveau1(joueur, plateau);
      break;

    case 20:
      attente(1);
      prof = tour - 20;
      jouer_coup_niveau2(joueur, plateau, prof);
      break;

    case 30:
      attente(1);
      prof = tour - 30;
      jouer_coup_niveau3(joueur, plateau);
      break;

    case 40:

      // jouer_coup_niveau4(joueur,plateau);
      break;

      /* TODO */
    }
    
    joueur = opposant(joueur);
    if(tour==infos.niv1){
	tour=infos.niv2;
    }
    else{
	tour=infos.niv1;
    }

       
#ifdef TEST
       f = 1;
#endif /* ifdef TEST */
  }
  fin(infos,joueur);
  return 1;
}

int opposant(int couleur) {
  if (couleur == NOIR) return BLANC;

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
  plateau[4][4] = plateau[5][5] = BLANC;
  plateau[5][4] = plateau[4][5] = NOIR;
}

// après selection de case verifie si pion peut etre posé
int pose_pion(int couleur, int i, int j, int **plateau) {
  // int acc;
  int valide = coup_valide(couleur, i, j, plateau);

  if (valide) plateau[i][j] = couleur;

  // else return 0;
  //
  int c_h=cap_haut( couleur,  i, j,  plateau);
  int c_b=cap_bas( couleur,  i,  j,  plateau);
  int c_d=cap_droit( couleur,  i,  j,  plateau);
  int c_g=cap_gauche( couleur,  i,  j,  plateau);
  int c_hd=cap_diag_haut_droit( couleur,  i,  j,  plateau);
  int c_hg=cap_diag_haut_gauche( couleur,  i,  j,  plateau);
  int c_bd=cap_diag_bas_droit( couleur,  i,  j,  plateau);
  int c_bg=cap_diag_bas_gauche( couleur,  i,  j,  plateau);
  int ibis, jbis;
  if(c_h){
      ibis=i-1;
      while(plateau[ibis][j]==opposant(couleur)){
	  plateau[ibis][j]=couleur;
	  ibis-=1;
      }
  }
  if(c_b){
      ibis=i+1;
      while(plateau[ibis][j]==opposant(couleur)){
	  plateau[ibis][j]=couleur;
	  ibis+=1;
      }
  }
  if(c_d){
      jbis=j+1;
      while(plateau[i][jbis]==opposant(couleur)){
	  plateau[i][jbis]=couleur;
	  jbis+=1;
      }
  }
 
  if(c_g){
      jbis=j-1;
      while(plateau[i][jbis]==opposant(couleur)){
	  plateau[i][jbis]=couleur;
	  jbis-=1;
      }
  } 
  if(c_hd){
      ibis=i-1;
      jbis=j+1;
      while(plateau[ibis][jbis]==opposant(couleur)){
	  plateau[ibis][jbis]=couleur;
	  ibis-=1;
	  jbis+=1;
      }
  }
  if(c_hg){
      ibis=i-1;
      jbis=j-1;
      while(plateau[ibis][jbis]==opposant(couleur)){
	  plateau[ibis][jbis]=couleur;
	  ibis-=1;
	  jbis-=1;
      }
  }
  
  if(c_bd){
      ibis=i+1;
      jbis=j+1;
      while(plateau[ibis][jbis]==opposant(couleur)){
	  plateau[ibis][jbis]=couleur;
	  ibis+=1;
	  jbis+=1;
      }
  }
    
  if(c_bg){
      ibis=i+1;
      jbis=j-1;
      while(plateau[ibis][jbis]==opposant(couleur)){
	  plateau[ibis][jbis]=couleur;
	  ibis+=1;
	  jbis-=1;
      }
  }
    
  return valide;
}

// OK
int cap_haut(int couleur, int i, int j, int **plateau) {
  int i_bis = i - 1, adv = 0;

  while (i_bis > 0) {
    if ((plateau[i_bis][j] == couleur) && (adv > 0)) return 1;

    if (plateau[i_bis][j] == VIDE) return 0;

    if(plateau[i_bis][j] == opposant(couleur))adv   += 1;
    i_bis -= 1;
  }
  return 0;
}

int cap_bas(int couleur, int i, int j, int **plateau) {
  int i_bis = i + 1, adv = 0;

  while (i_bis < 9) {
    if ((plateau[i_bis][j] == couleur) && (adv > 0)) return 1;

    if (plateau[i_bis][j] == VIDE) return 0;

    if(plateau[i_bis][j] == opposant(couleur))adv   += 1;
    i_bis += 1;
  }
  return 0;
}

int cap_droit(int couleur, int i, int j, int **plateau) {
  int j_bis = j + 1, adv = 0;

  while (j_bis < 9) {
    if ((plateau[i][j_bis] == couleur) && (adv > 0)) return 1;

    if (plateau[i][j_bis] == VIDE) return 0;

    if(plateau[i][j_bis] == opposant(couleur))adv   += 1;
    j_bis += 1;
  }
  return 0;
}

int cap_gauche(int couleur, int i, int j, int **plateau) {
  int j_bis = j - 1, adv = 0;

  while (j_bis > 0) {
    if ((plateau[i][j_bis] == couleur) && (adv > 0)) return 1;

    if (plateau[i][j_bis] == VIDE) return 0;

    if(plateau[i][j_bis] == opposant(couleur))adv   += 1;
    j_bis -= 1;
  }
  return 0;
}

// OK
int cap_diag_haut_droit(int couleur, int i, int j, int **plateau) {
  int i_bis = i - 1, j_bis = j + 1, adv = 0;

  while (i_bis > 0 || j_bis < 9) {
    if ((plateau[i_bis][j_bis] == couleur) && (adv > 0)) return 1;

    if (plateau[i_bis][j_bis] == VIDE) return 0;

    if(plateau[i_bis][j_bis] == opposant(couleur))adv   += 1;
    i_bis -= 1;
    j_bis += 1;
  }
  return 0;
}

// OK
int cap_diag_haut_gauche(int couleur, int i, int j, int **plateau) {
  int i_bis = i - 1, j_bis = j - 1, adv = 0;

  while (i_bis > 0 || j_bis > 0) {
    if ((plateau[i_bis][j_bis] == couleur) && (adv > 0)) return 1;

    if (plateau[i_bis][j_bis] == VIDE) return 0;

    if(plateau[i_bis][j_bis] == opposant(couleur))adv   += 1;
    i_bis -= 1;
    j_bis -= 1;
  }
  return 0;
}

// OK
int cap_diag_bas_droit(int couleur, int i, int j, int **plateau) {
  int i_bis = i + 1, j_bis = j + 1, adv = 0;

  while (i_bis < 9 || j_bis < 9) {
    if ((plateau[i_bis][j_bis] == couleur) && (adv > 0)) return 1;

    if (plateau[i_bis][j_bis] == VIDE) return 0;

    if(plateau[i_bis][j_bis] == opposant(couleur))adv   += 1;
    i_bis += 1;
    j_bis += 1;
  }
  return 0;
}

// OK
int cap_diag_bas_gauche(int couleur, int i, int j, int **plateau) {
  int i_bis = i + 1, j_bis = j - 1, adv = 0;

  while (i_bis < 9 || j_bis > 0) {
    if ((plateau[i_bis][j_bis] == couleur) && (adv > 0)) return 1;

    if (plateau[i_bis][j_bis] == VIDE) return 0;

    if(plateau[i_bis][j_bis] == opposant(couleur))adv   += 1;
    i_bis += 1;
    j_bis -= 1;
  }
  return 0;
}

int a_voisin(int i, int j, int **plateau) {
  // si on est au bord du plateau
  int vois;

  vois =
    plateau[i - 1][j - 1] +
    plateau[i - 1][j] +
    plateau[i - 1][j + 1] +
    plateau[i][j - 1] +
    plateau[i][j + 1] +
    plateau[i + 1][j - 1] +
    plateau[i + 1][j] +
    plateau[i + 1][j + 1];

  if (vois > 0) return 1;

  return 0;
}

int coup_valide(int couleur, int i, int j, int **plateau) {
  int s = 0;

  if (plateau[i][j] != VIDE) return 0;

  if (a_voisin(i, j, plateau)) {
    s = cap_haut(couleur,  i,  j,  plateau) + cap_bas(couleur,  i,  j,  plateau) +
        cap_droit(couleur, i, j, plateau) +
        cap_gauche(couleur, i, j, plateau) +
        cap_diag_haut_droit(couleur, i, j, plateau) +
        cap_diag_haut_gauche(couleur, i, j, plateau) +
        cap_diag_bas_droit(couleur, i, j, plateau) +
        cap_diag_bas_gauche(couleur, i, j, plateau);

    // fprintf(stderr,"^ %d, ^> %d, > %d, v> %d, v %d, <v %d, < %d, <^ %d\n",
    // cap_haut( couleur,  i,  j,  plateau),cap_diag_haut_droit( couleur,  i,
    //  j,  plateau),cap_droit( couleur,  i,  j,  plateau), cap_diag_bas_droit(
    // couleur,  i,  j,  plateau),cap_bas( couleur,  i,  j,
    //  plateau),cap_diag_bas_gauche( couleur,  i,  j,  plateau), cap_gauche(
    // couleur,  i,  j,  plateau),cap_diag_haut_gauche( couleur,  i,  j,
    //  plateau));
  }

  // fprintf(stderr,"coup %d\n",s);
  if (s >= 1) {
    return 1;
  }
  else {
    return 0;
  }
}

int* nb_pions(int **plateau) {
  int  i, j, b = 0, n = 0;
  int *blanc_noir = (int *)allocation_mem(3, sizeof(int));

  for (i = 1; i <= 8; i++)
    for (j = 1; j <= 8; j++) {
      if (plateau[i][j] == BLANC) b++;

      if (plateau[i][j] == NOIR) n++;
    }
  blanc_noir[0] = b + n;
  blanc_noir[1] = n;
  blanc_noir[2] = b;
  return blanc_noir;
}

int est_fini_partie(int couleur, int **plateau) {

  int *etat = nb_pions(plateau);

  // fprintf(stderr,"nb pions %d",etat[0]);
  int i, j;
  int c, b;

  if (etat[0] == 64) return 1;

  for (i = 1; i <= 8; i++)
    for (j = 1; j <= 8; j++) {
      c = coup_valide(couleur, i, j, plateau);
      b = coup_valide(opposant(couleur), i, j, plateau);
      // fprintf(stderr,"i %d j %d coup valide %d\n",i,j,c);
      if (c || b) return 0;
    }
  return 1;
}
