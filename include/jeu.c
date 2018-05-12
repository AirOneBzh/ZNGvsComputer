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



int jeu(int hauteur,int largeur, info infos) {
  // int   dh = hauteur_fenetre();
  // int   h  = 0.8 * dh;
  // int   c  = h / 18;
  // int   w  = 16 * h / 9;
  int **plateau;
  int   i;
  int   x, y, joueur = NOIR;


  x       = y = 0;
  plateau = allocation_mem(10, sizeof(int *));

  for (i = 0; i < 10; i++) {
    plateau[i] = allocation_mem_init0(10, sizeof(int));
  }

  // si menu load > tab = fich sinon init_pions
  init_pions(plateau);
  
  // creer fenetre
  creer_fenetre(hauteur,largeur, infos);

  //dess_
  dess_pions(plateau);
  dess_apercu_selec(0, 0);
  
  int r;

  // fin non atteinte
  //  !est_fini_partie(joueur,plateau)
  while (!est_fini_partie(joueur,plateau)) {
   
    r = att_souris_clav(&x, &y);

    // resultat de att souris
    switch (r) {
      // cadre de selection
      case 0:
      dess_apercu_selec(x, y);
      break;

      // clic souris ou entrée
      case 1:

      if (pose_pion(joueur, x, y, plateau) == 1) {
        // jb numero du joueur qui doit jouer 1 ou 2
	  joueur=opposant(joueur);
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
    dess_plat();
    dess_info(infos);
    dess_pions(plateau);
     dess_apercu_selec(x, y);
    
    #ifdef TEST
    f = 1;
    #endif /* ifdef TEST */
  }
  free_jeu();
  return 1;
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
  plateau[4][4] = plateau[5][5] = BLANC;
  plateau[5][4] = plateau[4][5] = NOIR;
}

// après selection de case verifie si pion peut etre posé
int pose_pion(int couleur, int x, int y, int **plateau) {
  // int i;
  int valide=coup_valide(couleur,x,y,plateau);
  if (valide)
  plateau[x][y]=couleur;
  return valide;
}
//OK
int cap_haut(int couleur, int i, int j, int **plateau){
    int i_bis=i-2, adv=0;
    while( i_bis > 0 ){
	if(plateau[i_bis][j]==couleur && adv > 0) return 1;
	if(plateau[i_bis][j]==VIDE) return 0;
	adv+=1;
	i_bis-=1;
    }
    else if(plateau[i_bis][j]==couleur){
      if(adv>0)
	return 1;
    }
    else{
      return 0;
    }
  }
    return 0;
}

int cap_bas(int couleur, int i, int j, int **plateau){
    int i_bis=i+2, adv=0;
    while( i_bis < 9 ){
	if(plateau[i_bis][j]==couleur && adv > 0) return 1;
	if(plateau[i_bis][j]==VIDE) return 0;
	adv+=1;
	i_bis+=1;
    }
  }
  return 0;
}

int cap_droit(int couleur, int i, int j, int **plateau){
    int j_bis=j+2, adv=0;
    while( j_bis < 9 ){
	if(plateau[i][j_bis]==couleur && adv > 0) return 1;
	if(plateau[i][j_bis]==VIDE) return 0;
	adv+=1;
	j_bis+=1;
    }
    return 0;
}

int cap_gauche(int couleur, int i, int j, int **plateau){
    int j_bis=j-2, adv=0;
    while( j_bis > 0 ){
	if(plateau[i][j_bis]==couleur && adv > 0) return 1;
	if(plateau[i][j_bis]==VIDE) return 0;
	adv+=1;
	j_bis-=1;
    }
    return 0;
}

//NOT OK
int cap_diag_haut_droit(int couleur, int i, int j, int **plateau){
    int i_bis=i-2, j_bis=j+2, adv=0;
    
    return 0;
}

int cap_diag_haut_gauche(int couleur, int i, int j, int **plateau){
    int i_bis=i-2, j_bis=j-2, adv=0;
    if( j_bis < 1 || i_bis < 1 )
	return 0;
    while( i_bis >=1  || j_bis >=1 ){
	if( plateau[i_bis][j_bis] == couleur && adv > 0 )
	    return 1;
	if (plateau[i_bis][j_bis] == VIDE )
	    return 0;
	else {
	    i_bis-=1;
	    j_bis-=1;
	    adv+=1;
	}
    }
    return 0;
}


int cap_diag_bas_droit(int couleur, int i, int j, int **plateau){
    int i_bis=i+2, j_bis=j+2, adv=0;
    if( j_bis > 8 || i_bis > 8 )
	return 0;
    while( i_bis <= 8 || j_bis <= 8 ){
	if( plateau[i_bis][j_bis] == couleur && adv > 0 )
	    return 1;
	if ( plateau[i_bis][j_bis] == VIDE )
	    return 0;
	else {
	    i_bis+=1;
	    j_bis+=1;
	    adv+=1;
	}
    }
    return 0;
}


int cap_diag_bas_gauche(int couleur, int i, int j, int **plateau){
    int i_bis=i+2, j_bis=j-2, adv=0;
    if( j_bis < 1 || i_bis > 8 )
	return 0;
    while( i_bis <= 8 || j_bis >=1 ){
	if( plateau[i_bis][j_bis] == couleur && adv > 0 )
	    return 1;
	if (plateau[i_bis][j_bis] == VIDE )
	    return 0;
	else{
	    i_bis+=1;
	    j_bis-=1;
	    adv+=1;
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
    fprintf(stderr,"vois        i %d, j %d, ^ %d, ^> %d, > %d, v> %d, v %d, <v %d, < %d, <^ %d\n",i,j,	plateau[i-1][j],plateau[i-1][j+1],plateau[i][j+1],plateau[i+1][j+1],plateau[i+1][j],plateau[i+1][j-1],plateau[i][j-1],plateau[i-1][j-1]);
    fprintf(stderr,"i %d j %d vois %d\n",i,j,vois);
    if( vois > 0)
	return 1;
    return 0;
}

int coup_valide(int couleur, int i, int j, int **plateau){
  int s=0;
  if(plateau[i][j] != VIDE ) return 0;
  if ( a_voisin(i, j, plateau) ){
    s= cap_haut( couleur,  i,  j,  plateau) + cap_bas( couleur,  i,  j,  plateau) +
      cap_droit( couleur,  i,  j,  plateau) +
      cap_gauche( couleur,  i,  j,  plateau) +
      cap_diag_haut_droit( couleur,  i,  j,  plateau) +
      cap_diag_haut_gauche( couleur,  i,  j,  plateau) +
      cap_diag_bas_droit( couleur,  i,  j,  plateau) +
      cap_diag_bas_gauche( couleur,  i,  j,  plateau);
    fprintf(stderr,"i %d, j %d, ^ %d, ^> %d, > %d, v> %d, v %d, <v %d, < %d, <^ %d\n",i,j, cap_haut( couleur,  i,  j,  plateau),cap_diag_haut_droit( couleur,  i,  j,  plateau),cap_droit( couleur,  i,  j,  plateau), cap_diag_bas_droit( couleur,  i,  j,  plateau),cap_bas( couleur,  i,  j,  plateau),cap_diag_bas_gauche( couleur,  i,  j,  plateau), cap_gauche( couleur,  i,  j,  plateau),cap_diag_haut_gauche( couleur,  i,  j,  plateau));
  }
  fprintf(stderr,"coup %d\n",s);
  if(s>=1){
    return 1;
  }
  else{
    return 0;
  }
}

int *nb_pions(int **plateau){
    int i, j, b=0, n=0;
    int *blanc_noir=(int *)allocation_mem(3, sizeof(int));
    for(i=1; i<=8; i++)
	for(j=1; j<=8; j++){
	    if(plateau[i][j]==BLANC)
		b++;
	    if(plateau[i][j]==NOIR)
		n++;
	}
    blanc_noir[0]=b+n;
    blanc_noir[1]=b;
    blanc_noir[2]=n;
    return blanc_noir;
}

int est_fini_partie(int couleur, int **plateau){
  fprintf(stderr,"fini?");
  int *etat=nb_pions(plateau);
  fprintf(stderr,"BLANC %d NOIR %d",BLANC ,NOIR);
  fprintf(stderr,"nb pions %d",etat[0]);
  int i, j;
  int c;
  if(etat[0]==64)
    return 1;
  for(i=1; i<=8; i++)
    for(j=1; j<=8; j++){
      c=coup_valide(couleur, i, j, plateau);
      fprintf(stderr,"i %d j %d coup valide %d\n",i,j,c);
      if(c)
	return 0;
    }
  return 1;
}
