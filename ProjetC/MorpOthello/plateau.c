#include "plateau.h"
#include <stdio.h>
#include <string.h>

/* Variables */
Plateau p;

void affect(int i, int j, char val)
{
    p.grille[i][j]=val;
}

/* affiche le plateau de jeu */
void affichage(){
    int i,j;
    printf("   ");
    for(i = 0; i < 15; i++){
        if(i < 10){
            printf(" %d ",i);
        }else{
            printf("%d ",i);
        }
    }
    printf("\n");
     for( i = 0 ; i < 10; i++){
         printf("%d  ",i);
        for( j = 0 ; j < 15; j++){
            printf(" %c ",p.grille[i][j]);
        }
        printf("\n");
     }
}

void initPlateau(){
    int i,j;
    for( i = 0 ; i < 10; i++){
        for( j = 0 ; j < 15; j++){
            affect(i,j,'.');
        }
    }
    affichage();
}

char getCase(int x, int y){
    if(!coupEnDehors(x,y)){
        return p.grille[x][y];
    }
    return '.';
}
