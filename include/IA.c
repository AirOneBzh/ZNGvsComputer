#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include "IA.h"
#include <string.h>
#define COEF 500
#define INF INT_MAX

int **copie_plateau(int **plateau){
    int i, **plateau_bis=(int **)allocation_mem(10, sizeof(int *));
    
    for(i=0; i<10; i++){
	plateau_bis[i]=(int *)allocation_mem(10, sizeof(int));
	memcpy (plateau_bis[i], plateau[i], 10*sizeof(int));
    }
    return plateau_bis;
}

int evaluation(int couleur, int **plateau){
    /*première version d'évaluation
    int *pions=nb_pions(plateau);
    if(couleur == BLANC)
	return pions[0]-pions[1];
    return pions[1]-pions[0];
    */
    int somme=0, i, j;
    int **tab_strat=(int **)allocation_mem(10, sizeof(int *));
    for(i=1; i<=8; i++)
	tab_strat[i]=(int *)allocation_mem(10, sizeof(int));
    //les coins
    tab_strat[1][1]=tab_strat[1][8]=tab_strat[8][1]=tab_strat[8][8]=500;
    //les cases encerclants les coins
    tab_strat[1][2]=tab_strat[2][1]=tab_strat[1][7]=tab_strat[7][1]=tab_strat[8][2]=tab_strat[2][8]=tab_strat[8][7]=tab_strat[7][8]=-150;
    tab_strat[2][2]=tab_strat[2][7]=tab_strat[7][7]=tab_strat[7][2]=-250;
    //30pts
    tab_strat[1][3]=tab_strat[3][1]=tab_strat[1][6]=tab_strat[6][1]=tab_strat[8][3]=tab_strat[3][8]=tab_strat[8][6]=tab_strat[6][8]=30;
    //10pts
    tab_strat[1][4]=tab_strat[1][5]=tab_strat[8][4]=tab_strat[8][5]=tab_strat[4][1]=tab_strat[4][8]=tab_strat[5][1]=tab_strat[5][8]=10;
    //0pt
    tab_strat[2][3]=tab_strat[2][4]=tab_strat[2][5]=tab_strat[2][6]=tab_strat[7][3]=tab_strat[7][4]=tab_strat[7][5]=tab_strat[7][6]=0;
    tab_strat[3][2]=tab_strat[4][2]=tab_strat[5][2]=tab_strat[6][2]=tab_strat[3][7]=tab_strat[4][7]=tab_strat[5][7]=tab_strat[6][7]=0;
    //2pts
    tab_strat[3][4]=tab_strat[3][5]=tab_strat[6][4]=tab_strat[6][5]=tab_strat[4][3]=tab_strat[5][3]=tab_strat[4][6]=tab_strat[5][6]=2;
    //16pts
    tab_strat[4][4]=tab_strat[4][5]=tab_strat[5][4]=tab_strat[5][5]=16;
    //1pts
    tab_strat[2][3]=tab_strat[2][4]=tab_strat[2][5]=tab_strat[2][6]=tab_strat[7][3]=tab_strat[7][4]=tab_strat[7][5]=tab_strat[7][6]=0;
    tab_strat[3][2]=tab_strat[4][2]=tab_strat[5][2]=tab_strat[6][2]=tab_strat[3][7]=tab_strat[4][7]=tab_strat[5][7]=tab_strat[6][7]=0;
    for(i=1; i<=8; i++)
	for(j=1; j<=8; j++)
	    if(plateau[i][j]==couleur)somme+=tab_strat[i][j];
    for(i=0; i<=10; i++)
	free(tab_strat[i]);
    free(tab_strat);
    return somme;
}

int minmax(int couleur, int min, int **plateau, int prof, liste l)
{//A LA FIN DU PROG ON CONNAIT LA NOTE POUR UN COUP choisie
    int i, j;
    int **plateau_bis=copie_plateau(plateau);
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
    int **plateau_bis=copie_plateau(plateau);
    int i, j;
    if( est_fini_partie(couleur, plateau_bis) )
	return evaluation(couleur, plateau);
    else{ //pour tous les successeurs
	for( i=1; i <= 8 ; i++ )
	    for( j=1; j <= 8; j++){
		if(couleur==min){
		    if( coup_valide(couleur, i, j, plateau_bis)){
			plateau_bis[i][j]=couleur;
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
	    }//fin for j
    }//fin for i
    return EXIT_FAILURE;//pas possible
}
int **jouer_coup_niveau0(int couleur, int **plateau){
    int i, j;
    int nb_coup=0;
    pile p=pile_vide();
    srand(time(NULL));
    for(i=1; i<=8; i++)
	for(j=1; j<=8; j++)
	    if(coup_valide(couleur, i, j, plateau)){
		empile_coup(i, j, p);
		nb_coup+=1;
	    }
    nb_coup=rand()%nb_coup;
    while(nb_coup>0)
	p=depile_coup(p);
    
    plateau[p->x][p->y]=couleur; // pose pion
    return plateau;
}

int **jouer_coup_niveau1(int couleur, int **plateau){
    //C'EST A couleur DE JOUER
    liste l=liste_vide();
    int **plateau_bis;
    int i, j, betterX, betterY, prof=2;
    int note = INT_MIN;
    for(i=1; i<=8; i++)
	for(j=1; j<=8; j++)
	    if(coup_valide(couleur, i, j, plateau)){//stocker les notes
		plateau_bis=copie_plateau(plateau);
		plateau_bis[i][j]=couleur;
		if( minmax(opposant(couleur),opposant(couleur), plateau_bis, prof-1, l) > note ){
		    betterX=i;
		    betterY=j;
		    note = minmax(opposant(couleur),opposant(couleur), plateau_bis, prof-1, l);
		}
		for(i=1; i<=10; i++)
		    free(plateau_bis[i]);
		free(plateau_bis);
	    }
    plateau[betterX][betterY]=couleur;
    return plateau;
}
  
int **jouer_coup_niveau2 (int couleur, int **plateau, int prof){
    //C'EST A couleur DE JOUER
    liste l=liste_vide();
    int **plateau_bis=copie_plateau(plateau);
    int i, j, x, y;
    int note = INT_MIN;
    for(i=1; i<=8; i++)
	for(j=1; j<=8; j++)
	    if(coup_valide(couleur, i, j, plateau)){//stock les notes
		plateau_bis=copie_plateau(plateau);
		plateau_bis[i][j]=couleur;  //pose pion
		if( minmax(opposant(couleur), opposant(couleur), plateau_bis, prof-1, l) > note ){
			x=i;
			y=j;
			note = minmax(opposant(couleur),opposant(couleur), plateau_bis, prof-1, l);
				      }
		for(i=1; i<=10; i++)
		    free(plateau_bis[i]);
		free(plateau_bis);
	    }
    plateau[x][y]=couleur; // pose pion
    return plateau;
}

int **jouer_coup_niveau3(int couleur, int **plateau){
    liste l=liste_vide();
    int **plateau_bis;
    int i, j, betterX, betterY;
    int note = INT_MIN;
    for(i=1; i<=8; i++)
	for(j=1; j<=8; j++)
	    if(coup_valide(couleur, i, j, plateau)){//stocker les notes
		plateau_bis=copie_plateau(plateau);
		plateau_bis[i][j]=couleur;
		if( alpha_beta(opposant(couleur), opposant(couleur), plateau_bis, INT_MIN, INT_MAX, l) > note ){
		    betterX=i;
		    betterY=j;
		    note = alpha_beta(opposant(couleur), opposant(couleur), plateau_bis, INT_MIN, INT_MAX, l);
		}
		for(i=1; i<=10; i++)
		    free(plateau_bis[i]);
		free(plateau_bis);
	    }
    plateau[betterX][betterY]=couleur;
    return plateau;
}

int **jouer_coup_niveau4(int couleur, int **plateau, pile Chemin, pile coup, int eval, int betterX, int betterY){
    int i, j;
    for(i=1; i<=8; i++){
	for(j=1; j<=8; j++){
	    if(coup_valide(couleur, i, j, plateau) ){
		if(  !est_fini_partie(couleur, plateau) ){
		    Chemin=ajoute_coup(couleur, i, j, plateau, Chemin);
		    jouer_coup_niveau4(opposant(couleur), plateau, Chemin, coup, eval, betterX, betterY);
		}
	     
		else { //la partie est finie on arrête d'empiler
		    if(eval<evaluation(couleur, plateau) ){ //on a trouvé un meileur coup!
			eval=evaluation(couleur, plateau);
			//on enlève tous les coups "test" joués
			while( !est_pile_vide(Chemin->suivant) )
			    Chemin=retire_coup(plateau, Chemin);
			//puis on récupère le coup à jouer
			betterX=Chemin->x;
			betterY=Chemin->y;
			Chemin=retire_coup(plateau, Chemin);
		    }
		    while( !est_pile_vide(Chemin) )
			Chemin=retire_coup(plateau, Chemin);
		}
	    }//fin de test si (i, j) est un coup valide	     
	}//fin for y
    }//fin for i
    //on vérifie si notre pile de coup possible est vide
    if( est_pile_vide(coup) ){//elle est vide on joue le meilleur coup
	plateau[betterX][betterY]=couleur;
    }
    else{ //le plateau n'est pas vide on continue de chercher d'autres possibilités
	coup=retire_coup(plateau, coup);
	plateau=jouer_coup_niveau4(couleur, plateau, Chemin, coup, eval, betterX, betterY);
    }
    return plateau;
}//end function
	     
