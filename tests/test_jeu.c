/*
*   Source TESTJEU_C
*
*   Fonctionnalités:
*   Tester Module jeu
*
*   Auteur: airone@airone-debian (E. LE CORNEC)
*   Création : 19/02
*/

#include <stdio.h>
#include <stdlib.h>
#include "../inc/jeu.h"
#include "../inc/allocation.h"
#include <string.h>
#ifndef TEST
#define TEST
#endif
int main(int argc,char *argv[]){
  if(argc<2 || strcmp(argv[1],"--help")==0){
    fprintf(stderr,"usage: test_jeu <fct>\nParmis:\n\tjeu\n\tinit_pions\n\tpose_pion\n\tretourne_pion_dir\n\tligne_pion_dir\n\nPour plus d'information sur ces fonctions \nAjouter --help après le nom de la fonction\n\n");
  }
  if(argc==2){
    if(strcmp(argv[1],"jeu")==0){
      jeu();
      exit(1);
    }
    if(strcmp(argv[1],"init_pions")){
      int i,j;
      int **tab=(int **)allocation_mem(8,sizeof(int*));
      for(i=0;i<8;i++){
        tab[i]=(int *)allocation_mem_init0(8,sizeof(int));
      }
      init_pions(tab);
      for(i=0;i<8;i++){
        for(j=0;j<8;j++){
          fprintf(stdout,"%d ",tab[i][j]);
        }
        printf("\n" );
      }
    }
  }
}
