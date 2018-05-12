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


// Créer une fenetre de taille hauteur * largeur
void creer_fenetre(int hauteur,int largeur,info info);

//libère la mémoire used par la fenetre
void free_jeu();
// Dessine les infos complémentaires au jeu
void dess_infos(info i);

// affiche écran de fin ZNG l'emporte
void affiche_fin_ZNG();

int largeur_fenetre();
int hauteur_fenetre();

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
void creer_fen_menu();
void bouton(float x,
            char *text);

int att_souris_menu(int *x);

#endif /* end of include guard: INTERFACE_H  */
