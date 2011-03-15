#include <stdlib.h>
#include <stdio.h>
#include "globals.h"

/** Ce fichier contiendra toutes les fonctions pour le jeu contre l'intelligence artificielle du jeu */

/* Affiche les options pour la difficulté */
void menuIA(){
    printf("====Jouer contre l'ordinateur====\n");
    printf("=================================\n");
    printf("== 1 - découverte  ==============\n");
    printf("== 2 - facile      ==============\n");
    printf("== 3 - moyen       ==============\n");
    printf("== 4 - difficile   ==============\n");
    printf("== 5 - retour      ==============\n");
    printf("=================================\n");
}

/* x et y sotn des pointeurs vers les coordonnees de la case choisie par l'ia */

/* l'ia la moins intelligente, se contente de jouer au hasard */
void IAdecouverte(int *x, int *y){
    *x=rand_a_b(0,9);
    *y=rand_a_b(0,14);
}

/* l'ia facile, assez rudimentaire, essaie d'aligner ses pions.*/
void IAfacile(int *x, int *y){

}

/* l'ia moyen attaque et défend en surveillant le joueur */
void IAmoyen(int *x, int *y){

}

/* l'ia difficile anticipe beaucoup plus. */
void IAdifficile(int *x, int *y){

}

/* Cette fonction retourne un nombre aléatoire entre a et b */
/* On suppose a<b*/
int rand_a_b(int a, int b){
    srand(time(NULL));
    return rand()%(b-a) +a;
}

/* Cette fonction permet au joueur de choisir l'ia ou de revenir au menu précédent */

int choisirDif(){
    int choix=-1;
    int end=0;
    scanf("%d",&choix);
    while(!end){
        if(choix<1 || choix>5){
            printf("Erreur, recommencez, tu pues\n");
            scanf("%d",&choix);
        }
        else end=1;
    }
    if(choix!=5){

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
    initPlateau();
    while(!isWinner){
       /* au joueur de jouer*/
        if(auJoueur){
            affichage();
            auJoueur--;
            isWinner=saisie();
            if(isWinner){
                printf("Congratulation vous avez vaincu l'ordinateur !\n");
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
                        isWinner=win(x,y);
                        convertir(x,y);
                    }
                    break;

                case 2:
                break;

                case 3:
                break;

                case 4:
                break;

                default:
                printf("Erreur inconnue\n");
                break;
            }
            if(isWinner){
                printf("Désolé, l'ordinateur est plus fort que vous, you suck ta môman !\n");
            }
        }
    }



}
