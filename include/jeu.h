/*
*   Header JEU_H
*   Fonctionnalités:
*   Lancer fenetre jeu
*   Auteur: airone@airone-debian (E. LE CORNEC)
*   Création : 18/02
*   MODIFICATION camil les "tab" deviennent "plateau"
*/
#ifndef _JEU_H_
#define _JEU_H_

#ifndef VIDE
//LES BORDS DE LA MATRICE DOIVENT ÊTRE VIDE ( égal à 0)
#define VIDE 0  //ne pas toucher car fonction a_voisin
#define NOIR 1
#define BLANC 2

#endif


//Description jeu
void jeu();

//ajouter commentaire:airone
void init_pions(int **plateau);

//ajouter commentaire : airone
int pose_pion(int j,int x,int y,int **plateau);

//ajouter commentaire: airone
void retourne_pion_dir(int x,int y,int i,int dir,int **plateau);

//ajouter commentaire airone
int ligne_pion_dir(int j,int x,int y,int dir,int **plateau);

//fonction de vérification d'enncadrement d'un pion ennemi
int cap_haut(int couleur, int i, int j, int **plateau);
int cap_bas(int couleur, int i, int j, int **plateau);
int cap_droit(int couleur, int i, int j, int **plateau);
int cap_gauche(int couleur, int i, int j, int **plateau);
int cap_diag_haut_droit(int couleur, int i, int j, int **plateau);
int cap_diag_haut_gauche(int couleur, int i, int j, int **plateau);
int cap_diag_bas_droit(int couleur, int i, int j, int **plateau);
int cap_diag_bas_gauche(int couleur, int i, int j, int **plateau);

//fonction de verification de pion voisin
int a_voisin(int i, int j, int **plateau);

//fonction renvoyant vrai si le coup est légal
int est_legal_coup(int couleur, int i, int j, int **plateau);

//renvoie une liste de coup possible à partir d'un plateau
liste coup_possible(int **plateau);

#endif /* end of include guard: _JEU_H_  */
