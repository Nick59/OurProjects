#include <stdio.h>
#include <string.h>
#include "globals.h"

void afficherMenu(){
    printf("=================================================\n");
    printf("===================MorpOthello===================\n");
    printf("====Tout le fun du Morpion et de l'Othello !=====\n");
    printf("=================================================\n\n");
    printf("Veuillez choisir une option dans le menu\n");
    printf("1 - Jouer contre l'ordinateur\n");
    printf("2 - Mode 2 joueurs (local)\n");
    printf("3 - Rejoindre une partie en ligne\n");
    printf("4 - Creer une partie en ligne\n");
    printf("5 - Afficher les scores\n");
    printf("6 - Mode Tournoi\n");
    printf("7 - Quitter\n");
}

int choisirOption(){
    int choix;
    int fin=0;
    while(!fin){
        scanf("%d",&choix);
        if(choix<1 || choix>7){ fin = 0; printf("Erreur, reessayez\n"); }

        else fin = 1;
    }
    return choix;
}
