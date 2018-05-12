#ifndef _PILE_H_
#define _PILE_H_
//Le module pile est nécessaire pour le niveau 4
#include "allocation.h"
#include <stddef.h>
typedef struct cellule{
    int x;
    int y;
    int couleur;
    struct cellule *suivant;
}struct_cellule;

typedef struct_cellule *pile;

pile pile_vide();

int est_pile_vide(pile p);

//jouer un coup et l'empiler
pile ajoute_coup(int color, int i, int j, int **plateau, pile P);


//retire un coup de la pile(depile) et du plateau
pile retire_coup(int **plateau, pile P);

#endif
