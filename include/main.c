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

int main(void) {
  // creer fenetre menu -> interface.c
  creer_fen_menu();
  int j = 1, x, c;
  info infos;

  while (j == 1) {
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
      break;
    case 2:
      fprintf(stderr,"Règles");
      break;
    case 3:
      fprintf(stderr,"Fenetre");
      break;
    case 4:
      fprintf(stderr,"Joueurs");
      break;
    default:
      break;
    }
    // free_fen_menu
   
  }
}
