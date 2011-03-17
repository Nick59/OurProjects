#include <stdlib.h>
#include <stdio.h>
#include "globals.h"

/** Ce fichier contiendra toutes les fonctions pour le jeu contre l'intelligence artificielle du jeu */

/* Affiche les options pour la difficulté */
void menuIA(){
    printf("====Jouer contre l'ordinateur====\n");
    printf("=================================\n");
    printf("== 1 - découverte  ==============\n");
    printf("== 2 - normale     ==============\n");
    printf("== 3 - difficile   ==============\n");
    printf("== 4 - retour menu ==============\n");
    printf("=================================\n");
}

/* x et y sont des pointeurs vers les coordonnees de la case choisie par l'ia */

/* l'ia la moins intelligente, se contente de jouer au hasard */
void IAdecouverte(int *x, int *y){
    *x=rand_a_b(0,9);
    *y=rand_a_b(0,14);
}

/* l'ia normale est défensive, i et j sont des pointeurs des coordonnees de la case choisie par le joueur*/
/* l'ia essaye juste de gener */
void IA(int *x, int *y, int *i, int *j){
    generAUn(x,y,i,j);
}

void IADifficile(int *x,int *y, int *i, int *j){
    /* si pions du joueur alignés, anticipation...*/
    if(win(*i,*j,*x,*y)!=0){
        generAUn(x,y,i,j);
    }
    else{
        /*alignement vertical : on bloque la colonne*/
        if(*i==*x){
            (*y)+=3;
        }
        /* aligment horizontal : on bloque la ligne*/
        else if(*j==*y){
            (*x)+=3;
        }
        /*aligment en diagonale... on bloque la diagonale*/
        else{
            (*x)+=3;
            (*y)+=3;
        }
    }
}

/* Cette fonction retourne un nombre aléatoire entre a et b */
/* On suppose a<b*/
int rand_a_b(int a, int b){
    srand(rand()*time(NULL));
    return rand()%(b-a) +a;
}

/* Cette fonction permet au joueur de choisir l'ia ou de revenir au menu précédent */

int choisirDif(){
    int choix=-1;
    int end=0;
    scanf("%d",&choix);
    while(!end){
        if(choix<1 || choix>4){
            printf("Erreur, recommencez\n");
            scanf("%d",&choix);
        }
        else end=1;
    }
    if(choix!=4){
        return choix;
    }
    else{
        lancerMenu();
    }
}

/* lance une partie contre l'IA, l'int difficulte contient le choix du joueur */
void jouerContreIA(int difficulte){
    jo1.couleur='B';
    affectJoueur(jo1);
    int isWinner = 0;
    int auJoueur = 1;
    int x=-1;
    int y=-1;
    int *i,*j;
    i=malloc(sizeof(int));
    j=malloc(sizeof(int));
    *i=0;
    *j=0;
    initPlateau();
    while(!isWinner){
        /* au joueur de jouer*/
        if(auJoueur){
            affichage();
            auJoueur--;
            isWinner=saisie(i,j);
            if(isWinner){
                printf("Félicitations vous avez vaincu l'ordinateur !\n");
            }
        }
        /* a l'ordi de jouer*/
        else{
            auJoueur++;
            switch(difficulte){
                case 1:
                    x=-1;
                    y=-1;
                    while(!coupValide(x,y)){
                        IAdecouverte(&x,&y);
                    }
                    if(coupValide(x,y)){
                        affect(x,y,'N');
                        convertir(x,y);
                        isWinner=(win(x,y,NULL,NULL)==1);
                    }
                    break;

                case 2:
                    printf("L'ordinateur choisit son coup...\n");
                    x=-1;
                    y=-1;
                    while(!coupValide(x,y)){;
                        IA(&x,&y,i,j);
                    }
                    if(coupValide(x,y)){
                        affect(x,y,'N');
                        convertir(x,y);
                        isWinner=(win(x,y,NULL,NULL)==1);
                    }
                break;

                case 3:
                    printf("L'ordinateur choisit son coup...\n");
                    x=-1;
                    y=-1;
                    int *a,*b;
                    while(!coupValide(x,y)){
                        IADifficile(&x,&y,i,j);
                    }
                    if(coupValide(x,y)){
                        affect(x,y,'N');
                        convertir(x,y);
                        isWinner=(win(x,y,NULL,NULL)==1);
                    }

                default:
                printf("Erreur inconnue\n");
                break;
            }
            if(isWinner){
                printf("Désolé, l'ordinateur est plus fort que vous !\n");
            }
        }
    }
}

/* renvoie aléatoirement une case à 3 cases de distance de la case (*i,*j)*/
void generAUn(int *x,int *y, int *i, int *j){
    *x=rand_a_b(0,10000);
    *y=rand_a_b(0,10000);

    if(*x%2==0){
        *x=(*i)-3;
    }
    else{
        *x=rand_a_b(0,10000);
        if(*x%2==0){
            *x=(*i)+3;
        }
        else{
            *x=*i;
        }
    }

    if(*y%2==0){
         *y=(*j)-3;
    }
    else{
        *y=rand_a_b(0,10000);
        if(*y%2==0 && *x!=(*i)){
            *y=(*j);
        }
        else{
            *y=(*j)+3;
        }
    }
}
