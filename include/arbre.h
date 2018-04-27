#ifndef _STRUCTURE_H_
#define _STRUCTURE_H_

#include "liste.h"

#define VIDE 0
#define BLANC 1
#define NOIR -1



typedef struct cell{//noeud d'un arbre exemple couleur[1][A]=BLANC
    int **actu;
    liste possible;
}struct_cell;

typedef struct_cell *arbre;


//Pourquoi j'ai mis ces fonctions ici??
//int position_gagnante(int **plateau); //plateau[8][8]

//int *coup_ordinateur(arbre A);

//int a_voisin(int *coup, int couleur_pion, int **plateau);

//int coup_valide(int *coup); //coup={x; y}

//int evaluation_plateau(arbre A); //attribue une note pour chaque branche

arbre creer_arbre_vide(); //pas de commentaire

arbre ajoute_noeud_arbre(arbre a, int **plateau, liste coup_possible);

arbre creer_arbre_position(int x, int y);//recursive creer un arbre de possibilitées à partir d'un coup joué

#endif
