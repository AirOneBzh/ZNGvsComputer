

#ifndef _LISTE_H_
#define _LISTE_H_

#include <stdio.h>
#include "allocation.h"
#include "mon_erreur.h"

typedef int element;

typedef struct cellule{
    int couleur[8][8];
    int note;
 struct cellule * suivant;
}struct_cellule;
typedef struct_cellule * liste;

/* renvoie la liste vide */
liste liste_vide();

/* teste si une liste est vide */
int est_liste_vide(liste l);

/*ajoute un element elem a la liste l */
liste insere_element_liste(liste l, element elem);

/* renvoie le premier element de la liste l */
element renvoie_premier_liste(liste l);

/*renvoie la suite de la liste*/
liste renvoie_suite(liste l);

/* supprime la premiere cellule de la liste l */
liste supprimer_premier_liste(liste l);

/*affichage d'une liste*/
void affiche_liste(liste l);

/*fonction d'ordre sur les elements*/
int est_avant(element e1,element e2);
#endif
