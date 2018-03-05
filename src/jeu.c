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


int pose_pion(int j,int x,int y,int **tab);
void aff_pions(int **tab);
void dess_plat();
void init_pions(int **tab);

void jeu(){
  int dh=MLV_get_desktop_height();
  int h=0.8*dh;
  int c=h/18;
  int w=16*h/9;
  int **tab;
  int i;
  int x,y,jb=0,j;
  int f=0;
  x=y=0;
  tab=allocation_mem(8,sizeof(int*));
  for(i=0;i<8;i++){
    tab[i]=allocation_mem_init0(8,sizeof(int));
  }

  MLV_create_window("","",w,h);
  dess_plat();
  dess_apercu_selec(0,0);
  init_pions(tab);
  dess_pions(tab);
  MLV_actualise_window();

  while(f==0){
    j=jb+1;
    dess_plat();
    if(att_souris_clav(&x,&y)==0){
      dess_apercu_selec(x,y);
    }
    else{
      if(pose_pion(j,x,y,tab)==1){
        jb=1-jb;
      }
      else{
        MLV_draw_rectangle(c*(2*x+1),c*(2*y+1),2*c,2*c,MLV_COLOR_RED);
      }
    }
    dess_pions(tab);
    MLV_actualise_window();

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

// après selection de case verifie si pion peut etre posé
int pose_pion(int j,int x,int y,int **tab){
  if(tab[x][y]==0 ){ // && ligne_pions(x,y) -> renvoyant 1 à 8 si ligne de l'autre couleur puis un de sa coul
    tab[x][y]=j;
    return 1; // pose valide
  }
  else{
    return 0; // pose invalide (pion déjà présent)
  }
}

int ligne_pion(int x,int y,int **tab){
  
}
