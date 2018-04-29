#ifndef _IA_H_
#define _IA_H


//avoir la couleur de l'ennemi
int opposant(int couleur);

//fonction d'évaluation simple
//on peur l'améliorer
int evaluation(int couleur, int **plateau);

//retourne une note
int minmax(int couleur, int **plateau, int prof);

//fonctions de l'IA retournant le plateau avec prochain coup à jouer
int **jouer_coup_niveau0(int couleur, int **plateau);

int **jouer_coup_niveau1(int couleur, int **plateau);

int **jouer_coup_niveau2(int couleur, int **plateau int prof);

int **jouer_coup_niveau3(int couleur, int **plateau);

int **jouer_coup_niveau4(int couleur, int **plateau);
#endif
