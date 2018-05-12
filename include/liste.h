#ifndef _LISTE_H_
#define _LISTE_H_

typedef int element;

typedef struct cell{
element objet;
struct cell * suivant;
}struct_cell;

typedef struct_cell * liste;

/* renvoie la liste vide */
liste liste_vide();

/* teste si une liste est vide */
int est_liste_vide(liste l);

/*ajoute un element elem a la liste l */
liste inserer_element_liste(liste l, element elem);

/* renvoie le premier element de la liste l */
element renvoie_premier_liste(liste l);

/* supprime la premiere cellule de la liste l */
liste supprimer_element_liste(liste l);

//pour l'implémentation de la fonction minmax
element min_liste(liste l); //retourne min de la liste
element max_liste(liste l); //retourne max de la liste

#endif
