#ifndef _ALLOCATION_H_
#define _ALLOCATION_H_
#include <stddef.h>
/*--------------------------------------------------------------------
 *fonction d'allocation de memoire du type defini par taille 
 *pour un nombre nobjets
 *alloue un espace de memoire de taille  nobjets*taille octets
 */
void * allocation_mem(size_t nobjets,size_t taille);


/*--------------------------------------------------------------------
 *fonction d'allocation de memoire du type defini par taille 
 *pour un nombre nobjets, l'espace mémoire est initialise à 0 (null)
 *alloue un espace de memoire de taille  nobjets*taille octets
 */
void * allocation_mem_init0(size_t nobjets,size_t taille);


/*--------------------------------------------------------------------
 *fonction qui realloue un espace memoire DEJA ALLOUE precedemment
 *avec une taille memoire differente
 * l'adresse memoire deja allouee est definie par (*ptr) 
 * l'espace alloue est de taille nobjets*taille octets
 */
void* reallocation_mem(void **pt, size_t nobjets,size_t taille);

/*--------------------------------------------------------------------
 *fonction qui libere de la memoire allouee à l'adresse mémoire 
 * definie par (*pt) 
 */
void libere_mem(void * *pt);

#endif

