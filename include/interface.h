/*
 *   Header INTERFACE_H
 *   Fonctionnalités:
 *   Gère fonctions environnement graphique
 *   Auteur: airone@airone-debian (E. LE CORNEC)
 *   Création : 10/02
 */
#ifndef INTERFACE_H
#define INTERFACE_H
#include "jeu.h"

// affiche écran de fin IA l'emporte
void affiche_fin_IA();

// affiche écran de fin ZNG l'emporte
void affiche_fin_ZNG();

//
int  fin();

// Dessine plateau en effacant le précédent
void dess_plat();

// Dessine le tableau de pions 0 rien 1 blanc 2 noir
void dess_pions(int **tab);

// Attends une intéraction souris ou clavier retourne 1 si le pion doit être
// posé
int att_souris_clav(int *x,
                    int *y);

// Affiche carré de séléction si déplacement clavier
void dess_apercu_selec(int x,
                       int y);


// interface Menu
void bouton(float x,
            char *text);

#endif /* end of include guard: INTERFACE_H  */
