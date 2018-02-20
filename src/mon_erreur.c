/**
 * Programme implémentant une fonction d'erreur personnelle
 *
 *
 * historique:
 *  creation le 30/01/2014 - A. Habrard
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "../inc/mon_erreur.h"


/*----
 * fonction definissant un message d'erreur,et affiche 'format',
 * peut prendre plusieurs args pour l'affichage de format
 */
void mon_erreur (char *format,...)
{
  va_list arg;

  va_start(arg,format);

  fprintf(stderr,"Erreur - ");

  vfprintf(stderr,format,arg);/*affichage de la chaine format*/

  va_end(arg);

  exit(EXIT_FAILURE);/*on sort de l'application, on utilise exit ici*/
}
