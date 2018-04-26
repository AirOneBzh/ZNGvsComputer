/*
 *    Fichier principal Othello
 *   Fonctionnalités:
 *   Lance menu et jeu du othello
 *   Auteur: airone@airone-debian (E. LE CORNEC)
 *   Création : a long time ago in a far far galaxy...
 */


#include <stdio.h>
#include <stdlib.h>
#include "../src/mon_erreur.h"
#include "../src/allocation.h"
#include "../src/jeu.h"
#include "../src/interface.h"
#include "MLV/MLV_all.h"

int main(void) {
  int dh = MLV_get_desktop_height();
  int h  = 0.5 * dh;
  int w  = 3 * h / 4;

  MLV_create_window("Menu zngOthello", "2", w, h);
  MLV_clear_window(MLV_rgba(100, 200, 150, 100));
  bouton(1,    "Jouer");
  bouton(2.75, "Règles");
  bouton(4.5,  "3");
  bouton(6.25, "4");

  MLV_actualise_window();
  MLV_wait_seconds(5);
  MLV_free_window();
  jeu();
}
