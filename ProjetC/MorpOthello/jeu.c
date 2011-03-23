#include "globals.h"
#include "jeu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Affectation de joueur joueurCourant = b*/
void affectJoueur(Joueur b){
    strcpy(joueurCourant.name,b.name);
    joueurCourant.couleur = b.couleur;
}


/* Permet de saisir un pion dans la grille */
/* Place les coordonnees dans les pointeurs x et y*/
int saisie(int *x, int *y){
    int end = 1 ;
    int a,b;
    a=b=-1;
    while(end){
        printf("Saisir la ligne\n");
        scanf("%d", x);
        printf("Saisir la colonne\n");
        scanf("%d", y);
        fflush(stdin);
        if(coupValide(*x,*y)){
            affect(*x,*y,joueurCourant.couleur);
            convertir(*x,*y);
            end = 0;
        }else{
            printf("Coordonnées Fausses\n");
        }
    }
    if(win(*x,*y,&a,&b)==1){
        return 1;
    }
    return 0;
}
/* Change le joueur Courant */
void switchJoueur(){
    if( strcmp(joueurCourant.name,jo1.name)== 0){
         affectJoueur(jo2);
    }else{
          affectJoueur(jo1);
    }
}

/* Cette fonction représente une manche, elle renvoie 1 si le joueur 1 gagne, sinon 2 */
int manche(){
    int *x=malloc(sizeof(int));
    int *y=malloc(sizeof(int));
    *x=0;
    *y=0;
    int isWinner = 0;
    initPlateau();
    while(!isWinner){
        switchJoueur();
        printf("Joueur %s, A vous !\n",joueurCourant.name);
        isWinner=saisie(x,y);
        affichage();
    }
    printf("%s a gagné la manche ;)\n",joueurCourant.name);
    if(strcmp(joueurCourant.name,jo1.name)==0){
        jo1.score++;
        return 1;
    }
    else{
        jo2.score++;
        return 2;
    }
}

void afficherPoints(){
    printf("%s : %d \n",jo1.name,jo1.score);
    printf("%s : %d \n",jo2.name,jo2.score);
}

/* debut de la partie */
void debutPartie(){
    char j1[256];
    char j2[256];
    printf("Salut joueur 1, comment tu t'appelles ?\n");
    scanf("%s",&j1);
    printf("Salut joueur 2, et toi, c'est quoi ton nom ?\n");
    scanf("%s",&j2);
    init2Joueur(j1,j2,0);
}


/* Joue une partie en 2 manches gagnantes */
/* Renvoie le vainqueur lors d'un tournoi */
/* tournoi : si 0 pas tournoi si 1 tournoi */
Joueur partie(int tournoi){
    char choix[5];
    if(!tournoi){
        debutPartie();
    }
    int numManche=jo1.score+jo2.score;
    while(jo1.score!=2 && jo2.score!=2){
        numManche++;
        afficherPoints();
        printf("Manche %d !\n",numManche);
        manche();
        if(jo1.score!=2 && jo2.score!=2 && !tournoi){
            printf("Continuer ? (oui/non)\n");
            scanf("%s",&choix);
            if(strcmp("non",choix)==0){
                sauvegardeEnCours(jo1,jo2);
                break;
            }
        }
    }
    if(jo1.score==2){
        jo1.partiesGagnees++;
        jo2.partiesPerdues++;
        printf("%s a gagné la partie !!! Félicitations !!!\n",jo1.name);
        if(tournoi){
            return jo1;
        }
    }
    else if(jo2.score==2){
        jo1.partiesPerdues++;
        jo2.partiesGagnees++;
        printf("%s a gagné la partie !!! Félicitations !!!\n",jo2.name);
        if(tournoi){
            return jo2;
        }
    }
    jo1.score=0;
    jo2.score=0;
    if(!tournoi){
        majJoueur(jo1);
        majJoueur(jo2);
    }
}

void tournoi(){
    Joueur winner1,winner2,winner;
    int i=1;
    char noms[4][256];
    printf("Le tournoi va bientôt commencer !\n");
    for(i=0;i<4;i++){
        printf("Joueur %d, saisi ton nom !\n",i+1);
        scanf("%s",&noms[i]);
    }
    init2Joueur(noms[0],noms[1],1);
    printf("%s et %s, ca va être à vous !\n",jo1.name,jo2.name);
    winner1=partie(1);
    init2Joueur(noms[2],noms[3],1);
    printf("%s et %s, ca va être à vous !\n",jo1.name,jo2.name);
    winner2=partie(1);
    init2Joueur(winner1.name,winner2.name,1);
    printf("%s et %s sont en finale, preparez vous... \n",jo1.name,jo2.name);
    winner=partie(1);
    printf("Le tournoi est terminé... Le vainqueur est ... \n\n");
    printf("¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤\n");
    printf("%s !!!!!!!\n",winner.name);
    printf("¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤\n");
}

void lancerMenu(){

  afficherMenu();
    int choix = choisirOption();
        switch(choix){
           case 1:
               menuIA();
               jouerContreIA(choisirDif());
               break;

           case 2:
               partie(0);
               break;
           case 3:
               clientSide();
               break;
           case 4:
               serverSide();
               break;
           case 5:
               afficherScores();
               break;
           case 6:
               tournoi();
               break;
           case 7:
               printf("Au revoir !\n");
               exit(1);
               break;
           default:
               printf("Erreur, reessayez\n");
               break;
        }
}
