#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <SDL.h>
#include "sdl.h"
#include "globals.h"
#define HAUTEUR 480
#define LARGEUR 720

SDL_Surface *ecranJeu;
/* Permet de saisir un pion dans la grille  en cliquant sur la case */
/* Place les coordonnees dans les pointeurs x et y*/
/* retourne -1 quand le joueur quitte, 1 si il y a un gagnant, 0 sinon */
int SaisieGraphique(int *x, int *y){
    SDL_Event event;
    int a,b;
    int continuer=1;
    a=b=-1;
    while (continuer){
        /* On attend la saisie*/
        printf("Cliquez sur une case... \n");
        retry:

        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_MOUSEBUTTONUP:
                *y = (event.button.x)/48;
                *x = (event.button.y)/48;
                break;

            case SDL_QUIT:
                return -1;
                break;

            default:
                goto retry; //Il est deconseille en regle generale d'utiliser les etiquettes (code illisible) ,
                break;      // Cependant j ai trouve ca utile ici.
        }

        if(coupValide(*x,*y)){
            affect(*x,*y,joueurCourant.couleur);
            convertir(*x,*y);
            continuer = 0;
        }
        else{
            printf("Coordonnées Fausses\n");
        }
    }

    if(win(*x,*y,&a,&b)==1){
        return 1;
    }

    return 0;
}

// i = nblignes j = nbcolonnes
void dessinePlateau(int i, int j){
    int x,y;
    SDL_Surface *lignes[i];
    SDL_Surface *colonnes[j];
    SDL_Surface *pionBlanc = SDL_LoadBMP("img/pionBlanc.bmp");
    SDL_Surface *pionNoir= SDL_LoadBMP("img/pionNoir.bmp");
    SDL_Rect position;

    for(x=0;x<i;x++){
        lignes[x]=SDL_CreateRGBSurface(SDL_HWSURFACE, j*(HAUTEUR/i),2, 32, 0, 0, 0, 0); // on initialise les surfaces

    }
    for(y=0;y<j;y++){
        colonnes[y]=SDL_CreateRGBSurface(SDL_HWSURFACE, 2,j*(HAUTEUR/i), 32, 0, 0, 0, 0);
    }

    // les lignes
    for(x=0;x<i;x++){
        position.x = 0;
        position.y = x*(HAUTEUR/i);
        SDL_FillRect(lignes[x], NULL, SDL_MapRGB(ecranJeu->format, 0, 0, 0));
        SDL_BlitSurface(lignes[x], NULL, ecranJeu, &position); // On colle
    }

    // les colonnes
    for(y=0;y<j;y++){
        position.x=y*(HAUTEUR/i);
        position.y=0;
        SDL_FillRect(colonnes[y],NULL,SDL_MapRGB(ecranJeu->format, 0, 0, 0));
        SDL_BlitSurface(colonnes[y],NULL, ecranJeu, &position);
    }

    // on place les pions

    for(x=0;x<i;x++){
        for(y=0;y<j;y++){
            if(getCase(x,y)=='B'){
                position.x=y*(HAUTEUR/i)+2;
                position.y=x*(HAUTEUR/i)+2;
                SDL_BlitSurface(pionBlanc,NULL, ecranJeu,&position);
            }
            else if(getCase(x,y)=='N'){

                position.x=y*(HAUTEUR/i)+2;
                position.y=x*(HAUTEUR/i)+2;
                SDL_BlitSurface(pionNoir,NULL, ecranJeu,&position);
            }
        }
    }

    SDL_Flip(ecranJeu);
    for (x = 0 ; x < i ; x++){
        SDL_FreeSurface(lignes[x]); // On libere la mémoire allouée aux cases
    }
    for(y=0;y<j;y++){
        SDL_FreeSurface(colonnes[y]);
    }

}


/* Prepare la SDL */
int renduGraphique(){
    ecranJeu = NULL; // Le pointeur qui va stocker la surface de l'écran
    SDL_Init(SDL_INIT_VIDEO);
    SDL_WM_SetIcon(SDL_LoadBMP("img/pionNoir.bmp"), NULL);

    ecranJeu = SDL_SetVideoMode(LARGEUR, HAUTEUR, 32, SDL_HWSURFACE); // On tente d'ouvrir une fenêtre
    if (ecranJeu == NULL) // Si l'ouverture a échoué, on écrit l'erreur et on arrête
    {
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_WM_SetCaption("MorpOthello", NULL);
    SDL_FillRect(ecranJeu, NULL, SDL_MapRGB(ecranJeu->format, 255, 255, 255));
    SDL_Flip(ecranJeu);
    return EXIT_SUCCESS;
}

