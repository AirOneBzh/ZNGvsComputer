#ifndef _IA_H_
#define _IA_H



//fonction d'évaluation simple
//on peur l'améliorer
int evaluation(int couleur, int **plateau);

//retourne la meiller note
int minmax(int couleur, int min, int **plateau, int prof);

//algo alpha-beta
int alpha_beta(int couleur, int min, int **plateau, int alpha, int beta, liste l);

//fonctions de l'IA retournant le plateau avec prochain coup à jouer
int **jouer_coup_niveau0(int couleur, int **plateau);

int **jouer_coup_niveau1(int couleur, int **plateau);

int **jouer_coup_niveau2(int couleur, int **plateau int prof);

int **jouer_coup_niveau3(int couleur, int **plateau);

int **jouer_coup_niveau4(int couleur, int **plateau);
#endif
