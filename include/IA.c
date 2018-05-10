#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include "AI.h"
#include "jeu.h"
#include "liste.h"
#define COEF 500
#define INF INT_MAX



int evaluation(int couleur, int **plateau){
  int *pions=nb_pions(plateau);
  if(couleur == BLANC)
  return pions[0]-pions[1];
  return pions[1]-pions[0];
}

int minmax(int couleur, int min, int **plateau, int prof, liste l)
{//A LA FIN DU PROG ON CONNAIT LA NOTE POUR UN COUP choisie
  int plateau_bis[10][10];
  int i, j;
  memcpy(plateau, plateau_bis, sizeof(plateau));
  if(prof == 0 || est_fini_partie(couleur, plateau_bis))
  l=inserer_element_liste(l, evaluation(couleur, plateau));

  else{
    for( i=1; i <= 8 ; i++ )
    for( j=1; j <= 8; j++)
    if(coup_valide(couleur, i, j, plateau_bis)){
      pose_pion(couleur, i, j, plateau_bis);
      return minmax(opposant(couleur), min, plateau_bis, prof-1, l);
    }
  }
  if( couleur == min )
  return min_liste(l);
  return max_liste(l);

}

int alpha_beta(int couleur, int min, int **plateau, int alpha, int beta, liste l){
    int plateau_bis[10][10];
    int i, j;
    memcpy(plateau, plateau_bis, sizeof(plateau));
    if( est_fini_partie(couleur, plateau_bis) )
	return evaluation(couleur, plateau);
    else{ //pour tous les successeurs
	for( i=1; i <= 8 ; i++ )
	    for( j=1; j <= 8; j++){
		if(couleur==min){
		    if( coup_valide(couleur, i, j, plateau_bis)){
			plateau_bis[i][i]=couleur;
			l=inserer_element_liste(l, beta);
			l=inserer_element_liste(l, alpha_beta(opposant(couleur), min, plateau_bis, alpha, beta, l));
			beta=min_liste(l);
			if( alpha >= beta )
			    return alpha;
			return beta;
		    }
		}
		else{ //couleur == opposant(min)
		    if ( coup_valide(couleur, i, j, plateau_bis) ){
			plateau_bis[i][j]=couleur;
			l=inserer_element_liste(l, alpha);
			l=inserer_element_liste(l, alpha_beta(opposant(couleur), min, plateau_bis, alpha, beta, l));
			alpha=max_liste(l);
			if(alpha >= beta)
			    return beta;
			return alpha;   
		    }
		}
	    }
    }
}



      }
      else{
      }
    }
  }
}

int **jouer_coup_niveau0(int couleur, int plateau){
  int i, j;
  srand(time(NULL));
  i=1+rand()%8;
  j=1+rand()%8;
  if(coup_valide(couleur, i, j, plateau)){
    plateau[i][j]=couleur; // pose pion
    return plateau;
  }
  else jouer_coup_niveau0(couleur, plateau);
}

int **jouer_coup_niveau1(int couleur, int **plateau){
  //C'EST A couleur DE JOUER
  liste l=liste_vide();
  int **plateau_bis;
  memcpy(plateau, plateau_bis, sizeof(plateau));
  int i, j, x, y;
  int note = INT_MIN;
  for(i=1; i<=8; i++)
  for(j=1; j<=8; j++)
  if(coup_valide(couleur, i, j, plateau)){//stock les notes
    memcpy(plateau, plateau_bis, sizeof(plateau));
    int i, j, x, y;
    int note = INT_MIN;
    for(i=1; i<=8; i++)
	for(j=1; j<=8; j++)
	    if(coup_valide(couleur, i, j, plateau)){//stocker les notes
		memcpy(plateau, plateau_bis, sizeof(plateau));
		plateau_bis[i][j]=couleur;
		if( minmax(opposant(couleur), plateau_bis, prof-1) > note ){
		    x=i;
		    y=j;
		    note = minmax(opposant(couleur), plateau_bis, prof-1);
		}
	    }
    plateau[x][y]=couleur;
    return plateau;
}
int jouer_coup_niveau2 (int couleur, int **plateau, int prof){
  //C'EST A couleur DE JOUER
  liste l=liste_vide();
  int **plateau_bis;
  memcpy(plateau, plateau_bis, sizeof(plateau));
  int i, j, x, y;
  int note = INT_MIN;
  for(i=1; i<=8; i++)
  for(j=1; j<=8; j++)
  if(coup_valide(couleur, i, j, plateau)){//stock les notes
    memcpy(plateau, plateau_bis, sizeof(plateau));
    plateau_bis[i][j]=couleur;  //pose pion
    if( minmax(opposant(couleur), plateau_bis, prof-1) > note ){
      x=i;
      y=j;
      note = minmax(opposant(couleur), plateau_bis, prof-1);
    }
  }
  plateau[x][y]=couleur; // pose pion
  return plateau;
}

int jouer_coup_niveau3(int couleur, int **plateau){
    liste l=liste_vide();
    int **plateau_bis;
    memcpy(plateau, plateau_bis, sizeof(plateau));
    int i, j, x, y;
    int note = INT_MIN;
       for(i=1; i<=8; i++)
	for(j=1; j<=8; j++)
	    if(coup_valide(couleur, i, j, plateau)){//stocker les notes
		memcpy(plateau, plateau_bis, sizeof(plateau));
		plateau_bis[i][j]=couleur;
		if( alpha_beta(opposant(couleur), plateau_bis, INT_MIN, INT_MAX, l) > note ){
		    x=i;
		    y=j;
		    note = alpha_beta(opposant(couleur), plateau_bis, INT_MIN, INT_MAX, l);
		}
	    }
    plateau[x][y]=couleur;
    return plateau;
}
