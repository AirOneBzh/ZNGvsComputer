#include <stdio.h>
#include <stdlib.h>
#include "allocation.h"
#include "arbre.h"
#include "jeu.h"

arbre creer_arbre_vide(){
    return NULL;
}

arbre ajoute_noeud_arbre(arbre a, int **plateau, liste coup_possible){
    arbre abis=(arbre)allocation_mem(1, sizeof(struct_cell));
    abis->actu=plateau;
    abis->possible=coup_possible;
    a->possible
}//TODO






arbre creer_arbre_position(int x, int y, int **plateau);
    
