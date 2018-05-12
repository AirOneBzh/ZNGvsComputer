#include "pile.h"
#include "jeu.h"
pile pile_vide(){
    return NULL;
}

int est_pile_vide(pile p){
    if(p==pile_vide())
	return 1;
    return 0;
}

pile ajoute_coup(int color, int i, int j, int **plateau, pile P){
    //on ajoute le coup sur la pile
    pile pnew=(pile)allocation_mem(1, sizeof(struct_cellule));
    pnew->x=i;
    pnew->y=j;
    pnew->couleur=color;
    pnew->suivant=P;

    //mtn on ajoute le coup sur le plateau
    plateau[i][j]=color;
    return pnew;
}

pile retire_coup(int **plateau, pile P){
    //il suffit de retirer le coup dépiler du plateau
    int i, j;
    plateau[P->x][P->y]=VIDE;

    //puis de dépiler ce coup de la pile
    pile pnew=P->suivant;
    libere_mem(&P);
    return pnew;
}
 
