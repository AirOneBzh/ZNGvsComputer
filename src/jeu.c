/*
*   Source JEU_C
*   Fonctionnalités:
*   Dessiner le plateau de jeu et gérer les manip du tableau de pions
*   Auteur: airone@airone-debian (E. LE CORNEC)
*   Création :04/03/18
*/


#include <stdio.h>
#include <stdlib.h>
#include "../inc/mon_erreur.h"
#include "../inc/allocation.h"
#include "../inc/interface.h"
#include "MLV/MLV_all.h"



void aff_pions(int **tab);
void dess_plat();
void init_pions(int **tab);

void jeu(){
  int dh=MLV_get_desktop_height();
  int h=0.8*dh;
  int w=16*h/9;
  int **tab;
  int i;
  int x,y;
  x=y=0;
  tab=allocation_mem(8,sizeof(int*));
  for(i=0;i<8;i++){
    tab[i]=allocation_mem_init0(8,sizeof(int));
  }

  MLV_create_window("","",w,h);
  dess_plat();
  init_pions(tab);
  dess_pions(tab);
  MLV_actualise_window();
  for(i=0;i<5;i++){
    att_souris_clav(&x,&y);
    fprintf(stdout,"x%d y%d\n",x,y);
  }
  MLV_free_window();
}

void init_pions(int **tab){
  int i,j;
  for(i=0;i<8;i++){
    for(j=0;j<8;j++){
      tab[i][j]=0;
    }
  }
  tab[4][4]=tab[3][3]=1;
  tab[4][3]=tab[3][4]=2;
}
