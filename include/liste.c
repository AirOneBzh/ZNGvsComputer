#include <stdio.h>
#include <stdlib.h>
#include "liste.h"
#include <limits.h>

liste liste_vide()
{
  return NULL;
}

int est_liste_vide(liste l)
{
  if(l==liste_vide())
    return 1;
  return 0;
}

liste inserer_element_liste(liste l,element elem)
{
  liste lnew=(liste)malloc(sizeof(struct_cell));
  lnew->objet = elem;
  lnew->suivant=l;
  return lnew;
}



element renvoie_premier_liste(liste l)
{
  if(est_liste_vide(l))
    printf("Erreur la liste est vide dans la fonction renvoie_premier\n");
  return l->objet;
}

liste supprimer_element_liste(liste l)
{
  liste lsuivant=l->suivant;
  free(l);
  return lsuivant;
}

element min_liste(liste l){
    int acc=INT_MAX;
    liste lbis=l;
    while ( !est_liste_vide(lbis) ){
	if( lbis -> objet <= acc )
	    acc=lbis->objet;
	lbis=lbis->suivant;
    }
    return acc;
}

element max_liste(liste l){
    int acc=INT_MIN;
    liste lbis=l;
    while ( !est_liste_vide(lbis) ){
	if( lbis -> objet >= acc )
	    acc=lbis->objet;
	lbis=lbis->suivant;
    }
    return acc;
}
