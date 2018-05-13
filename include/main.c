/*
 *    Fichier principal Othello
 *   Fonctionnalités:
 *   Lance menu et jeu du othello
 *   Auteur: airone@airone-debian (E. LE CORNEC)
 *   Création : a long time ago in a far far galaxy...
 */


#include <stdio.h>
#include <stdlib.h>
#include "mon_erreur.h"
#include "allocation.h"
#include "jeu.h"
#include "interface.h"
#include <string.h>

void change_nom(char *nom){
  int correct=0;
  while(correct==0){
    correct=input_char(nom);
    if(strlen(nom)<2 && strlen(nom)>8){
      correct=0;
    }
  }
}

void change_joueuria(int *niv){
  int correct=0;
  while(correct==0){
    correct=input_int(niv);
    if(*niv>4 || *niv<-1){
      correct=0;
    }
  }
}

void joueurs(info *info){
  clean_fen_menu();
  char btn1[25], btn2[25],btn3[25],btn4[25];
  int c,q=0;
  
  while(q==0){
    
    sprintf(btn1,"Nom %s:",info->joueur_1);
    sprintf(btn2,"J / IA : %d",info->niv1);
    sprintf(btn3,"Nom %s:",info->joueur_2);
    sprintf(btn4,"J / IA : %d",info->niv2);
  

    bouton(   1, btn1);

    // change nom j1
    bouton(2.75, btn2);

    // change joueur / IA 1
    bouton( 4.5, btn3);

    // modifie Joueur 1 -> IA nom
    bouton(6.25, btn4);

    c = att_souris_menu(NULL);
    switch(c){
    case 1:
      change_nom(info->joueur_1);
      break;
    case 2:
      change_joueuria(&info->niv1);
      break;
    case 3:
      change_nom(info->joueur_2);
      break;
    case 4:
      change_joueuria(&info->niv2);
      break;
    case 5:
      q=1;
    default:
      break;
    }
  }
}




int main(void) {
  // creer fenetre menu -> interface.c
  
  int j = 1, x, c;
  info infos;
  strcpy(infos.joueur_1,"Joueur 1");
  strcpy(infos.joueur_2,"Joueur 2");
  infos.niv1=-1;
  infos.niv2=-1;
  creer_fen_menu();
  while (j == 1) {
    clean_fen_menu();
    // lance le jeu
    bouton(   1, "Jouer");

    // affiche les règles
    bouton(2.75, "Règles");

    // Modifie apparence fenetre
    // taille
    bouton( 4.5, "Fenetre");

    // modifie Joueur 1 -> IA nom
    bouton(6.25, "Joueurs");

    c = att_souris_menu(&x);
    switch(c){
    case 1:
      free_jeu();
      jeu(hauteur_fenetre(),largeur_fenetre(),infos);
      fprintf(stderr,"case");
      break;
    case 2:
      system("evince assets/Livret.pdf");
      break;
    case 3:
      fprintf(stderr,"Fenetre");
      break;
    case 4:
      joueurs(&infos);
      break;
    case 5:
      exit(EXIT_SUCCESS);
    default:
      break;
    }

    // free_fen_menu

  }
      free_jeu();
}
