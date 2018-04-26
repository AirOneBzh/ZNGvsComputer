/*
*   Header JEU_H
*   Fonctionnalités:
*   Lancer fenetre jeu
*   Auteur: airone@airone-debian (E. LE CORNEC)
*   Création : 18/02
*/
#ifndef JEU_H
#define JEU_H

#ifndef VIDE

#define NOIR -1
#define VIDE 0
#define BLANC 1

#endif


//Description jeu
void jeu();
void init_pions(int **tab);
int pose_pion(int j,int x,int y,int **tab);
void retourne_pion_dir(int x,int y,int i,int dir,int **tab);
int ligne_pion_dir(int j,int x,int y,int dir,int **tab);

#endif /* end of include guard: JEU_H  */
