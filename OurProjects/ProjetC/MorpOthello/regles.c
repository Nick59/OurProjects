#include "regles.h"
#include "globals.h"
#include <stdio.h>
#include <stdlib.h>

/*****

le fichier regles.c contient toutes les regles du jeu, comme les conditions de victoire, les placements autorises,...

******/

/* Cette fonction permet de changer la couleur des pions entoures apres un coup */
/* x et y representent les coordonnees du dernier pion place */
void convertir(int x, int y){

    int i,j;
    i=x;
    j=y;
    char couleur=p.grille[x][y];
    char adversaire;
    if(couleur=='B'){
        adversaire='N';
    }
    else{
        adversaire='B';
    }
    for(i=-1;i<2;i++){
        for(j=-1;j<2;j++){
            changerCouleur(x,y,i,j,couleur, adversaire);
        }
    }

}

/* Cette fonction change eventuellement de couleur les pions entoures*/
/* ivoisin et jvoisin peuvent valoir -1, 0, 1
    ce sont des coefficients permettant de changer la direction
    La fonction retourne 1 si il y a un un changement, 0 sinon*/
int changerCouleur(int i, int j, int ivoisin, int jvoisin, char couleur, char adversaire){
        if(getCase(i+(1*ivoisin),j+(1*jvoisin))==adversaire){
            if(getCase(i+(2*ivoisin),j+(2*jvoisin))==adversaire){
                if(getCase(i+(3*ivoisin),j+(3*jvoisin))==couleur){
                    affect(i+(1*ivoisin),j+(1*jvoisin),couleur);
                    affect(i+(2*ivoisin),j+(2*jvoisin),couleur);
                }
            }
            else if(getCase(i+(2*ivoisin),j+(2*jvoisin))==couleur){
                 affect(i+(1*ivoisin),j+(1*jvoisin),couleur);
            }
            return 1;
        }
        else{
            return 0;
        }
}
/* Cette fonction retourne 1 si le joueur courant gagne*/
/* Sinon, les autres nombres correspondent au nombre de pions alignés (2,3,4) */
/* i et j sont les coordonnees du dernier coup joue*/
/* x et y sont des pointeurs vers la fin de l'alignement*/
int win(int i, int j, int *x, int *y){
    int ivoisin=0;
    int jvoisin=0;
    char couleur=p.grille[i][j];
    for(ivoisin=-1;ivoisin<2;ivoisin++){
        for(jvoisin=-1;jvoisin<2;jvoisin++){
            if(ivoisin!=0 || jvoisin !=0){
                if(getCase(i+(1*ivoisin),j+(1*jvoisin))==couleur){
                    if(getCase(i+(2*ivoisin),j+(2*jvoisin))==couleur){
                        if(getCase(i+(3*ivoisin),j+(3*jvoisin))==couleur){
                            if(getCase(i+(4*ivoisin),j+(4*jvoisin))==couleur){
                                return 1;
                            }
                            *x=i+(3*ivoisin);
                            *y=j+(3*ivoisin);
                            return 4;
                        }
                        *x=i+(2*ivoisin);
                        *y=j+(2*ivoisin);
                        return 3;
                    }
                    *x=i+(1*ivoisin);
                    *y=j+(1*ivoisin);
                    return 2;
                }
            }
        }
    }
    return 0;
}

/* Cette fonction retourne vrai si les coordonnees ne sont pas dans le plateau */
int coupEnDehors(int i, int j){
 if(i<0 || i > 9 || j < 0 || j > 14){
     return 1;
 }
 return 0;
}


/* Cette fonction retourne 0 si le coup n'est pas valide, 1 sinon */

int coupValide(int i, int j){
    if(coupEnDehors(i,j)){
        return 0;
    }
    if(p.grille[i][j]!='.'){
        return 0;
    }
    return 1;
}
