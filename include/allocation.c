#include <stdio.h>
#include <stdlib.h>
#include "mon_erreur.h"
#include "allocation.h"

/*--------------------------------------------------------------------
*fonction d'allocation de memoire du type defini par taille
*pour un nombre nobjets
*alloue un espace de memoire de taille  nobjets*taille octets
*/
void * allocation_mem(size_t nobjets,size_t taille)
{
  void * pt;

  pt = malloc (nobjets * taille);/*allocation*/

  /* on verifie si l'allocation a marche*/
  if (pt==NULL)
  mon_erreur("Impossible d'allouer la memoire %d %d\n",nobjets,taille);

  return(pt);
}


/*--------------------------------------------------------------------
*fonction d'allocation de memoire du type defini par taille
*pour un nombre nobjets, l'espace m�moire est initialise � 0 (null)
*alloue un espace de memoire de taille  nobjets*taille octets
*/
void * allocation_mem_init0(size_t nobjets,size_t taille)
{
  void * pt;

  pt = calloc (nobjets,taille);/*allocation avec calloc*/

  /* on verifie si l'allocation a marche*/
  if (pt==NULL)
  mon_erreur("Impossible d'allouer la memoire %d * %d\n",nobjets,taille);

  return(pt);
}


/*--------------------------------------------------------------------
*fonction qui realloue un espace memoire DEJA ALLOUE precedemment
*avec une taille memoire differente
* l'adresse memoire deja allouee est definie par (*ptr)
* l'espace alloue est de taille nobjets*taille octets
*/
void* reallocation_mem(void **pt, size_t nobjets,size_t taille)
{
  void *pt_realloc = realloc(*pt, nobjets*taille);
  if (pt_realloc != NULL)
  *pt = pt_realloc;
  else
  mon_erreur("Impossible de reallouer la memoire %d * %d a l'adresse %p\n",nobjets,taille,*pt);

  return pt_realloc;
}

/*--------------------------------------------------------------------
*fonction qui libere de la memoire allouee � l'adresse m�moire
* definie par (*pt)
* (*pt) est mis a NULL pour bien indique qu'il ne pointe sur rien
*version p�dagogique qui force � entrer un adresse de pointeur
*mais qui n�cessite un "cast" pour �viter un warning
*/
void libere_mem_peda(void * *pt)
{
  if((*pt)!=NULL)
  free(*pt); /*liberation de *pt */

  *pt=NULL; /* *pt pointe maintenant sur NULL, cad rien*/
}


/*--------------------------------------------------------------------
*fonction qui libere de la memoire allouee en *pt
*et place le pointeur � NULL
*ICI on suppose que pt est l'adresse de la variable allou�e
*n�cessaire pour pouvoir lib�r�.
*attention pt doit en fait �tre un void **
*/
void libere_adr(void *pt)
{
  void ** adr_pt=(void **) pt; // on suppose que pt est l'adresse de pointeur � lib�rer
  if((*adr_pt)!=NULL){
    free(*adr_pt);
    /*liberation de *pt */
  }
  *adr_pt=NULL; /* *pt pointe maintenant */
}


/*--------------------------------------------------------------------
*fonction qui libere de la memoire allouee en pt mais il n'y a pas de
*controle sur la valeur de pt en sortie de fonction
*/
void libere(void *pt)
{
  free(pt); /*liberation de *pt */
}
