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

void joueurs(info *info){
  clean_fen_menu();
  bouton(   1, "Nom Joueur 1:");

  // affiche les règles
  bouton(2.75, "Joueur / IA ");

  // Modifie apparence fenetre
  // taille
  bouton( 4.5, "Nom Joueur 2:");

  // modifie Joueur 1 -> IA nom
  bouton(6.25, "Joueur / IA");
  int c = att_souris_menu(NULL);
    switch(c){
    case 1:
      
      break;
    case 2:
      
      break;
    case 3:
      fprintf(stderr,"Fenetre");
      break;
    case 4:
     
      break;
    case 5:
      exit(EXIT_SUCCESS);
    default:
      break;
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
