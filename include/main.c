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
#include <ctype.h>

void change_nom(char *nom){
  int correct=0;
  while(correct==0){
    input("   Nom joueur   ",nom);
    if(strlen(nom)<2 || strlen(nom)>8){
      correct=0;
    }
    else
      correct=1;
  }
}

void change_joueuria(int *niv){
  int correct=0;
  char in[15];
  int i,prof;
  while(correct==0){
    input("    Joueur (-1) / IA (0->4)   ",in);
    fprintf(stderr,"%s",in);
    for(i=0;i<strlen(in);i++){
      if(!isdigit(in[i])){
	correct=0;
      }
      else{
	correct=1;
      }
    }
    if(correct==1){
      *niv=atoi(in)*10;
      if(*niv>40  || *niv<-10){
	correct=0;
      }
    }
  }
  if(*niv==20){
    correct=0;
    while(correct==0){
      input("    Profondeur IA (1->9)   ",in);
     for(i=0;i<strlen(in);i++){
       if(!isdigit(in[i])){
	correct=0;
       }
       else{
	 correct=1;
	 fprintf(stderr,"c1");
       }
    }
      if(correct==1){
	prof=atoi(in);
	*niv+=atoi(in);
	fprintf(stderr,"%d",*niv);
	if(prof<1 || prof>9){
	  correct=0;
	}
      }
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
    bouton(8, "Retour");

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
  infos.niv1=-10;
  infos.niv2=0;
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
    bouton(8, "Quitter");

    c = att_souris_menu(&x);
    switch(c){
    case 1:
      free_jeu();
      jeu(hauteur_fenetre(),largeur_fenetre(),infos);
      fprintf(stderr,"Retour Menu\n");
      resize_fen_menu();
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
