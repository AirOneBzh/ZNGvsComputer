//!!!!!A MODIFIER !!!!!

#include <stdio.h>
#include "liste.h"

/*retour liste vide*/
liste liste_vide()
{
  return NULL;
}

/*test liste vide*/
int est_liste_vide(liste l)
{
  if(l==liste_vide())
    return 1;
  return 0;
}

/*insertion element au debut de la liste*/
liste insere_element_liste(liste l,element elem)
{
  liste lnew=(liste)allocation_mem(1,sizeof(struct_cellule));
  lnew->objet=elem;
  lnew->suivant=l;
  return lnew;
}

/*renvoie le premier element de la liste, erreur sinon*/
element renvoie_premier_liste(liste l)
{
  if(est_liste_vide(l))
   mon_erreur("Erreur la liste est vide dans la fonction renvoie_premier\n");
  return l->objet;
}

/*renvoie la suite de la liste, liste_vide sinon*/
liste renvoie_suivant_liste(liste l)
{
  if(est_liste_vide(l))
    return l;
  return l->suivant;
}

/*supprimer le premier de la liste*/
liste supprimer_premier_liste(liste l)
{
  liste lsuivant=l->suivant;
  libere_mem((void**)&l);
  return lsuivant;
}

/*affichage d'une liste*/
void affiche_liste(liste l)
{
  liste p=l;

  while(!est_liste_vide(p))
    {
      printf("%d ",p->objet);
      p=p->suivant;
    }
  printf("\n");

}

/*fonction d'ordre sur les elements*/
int est_avant(element e1,element e2)
{
  if(e1<e2)
    return 1;
  return 0;
}
