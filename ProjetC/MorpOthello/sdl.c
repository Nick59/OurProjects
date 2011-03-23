#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "globals.h"
#define HAUTEUR 480
#define LARGEUR 640

void pauseEcran()
{
    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}
// i = nblignes j = nbcolonnes
void dessinePlateau(int i, int j, SDL_Surface *ecran){
    int x,y;
    SDL_Surface *lignes[i+1];
    SDL_Surface *colonnes[j+1];
    SDL_Rect position;
    for(x=0;x<=i;x++){
        lignes[x]=SDL_CreateRGBSurface(SDL_HWSURFACE, HAUTEUR,2, 32, 0, 0, 0, 0); // on initialise les surfaces

    }
    for(y=0;y<=j;y++){
        colonnes[y]=SDL_CreateRGBSurface(SDL_HWSURFACE, 2,i*(HAUTEUR/j), 32, 0, 0, 0, 0);
    }

    // les lignes
    for(x=0;x<=i;x++){
        position.x = 0;
        position.y = x*(HAUTEUR/j);
        SDL_FillRect(lignes[x], NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
        SDL_BlitSurface(lignes[x], NULL, ecran, &position); // On colle
    }

    // les colonnes
    for(y=0;y<=j;y++){
        position.x=y*(HAUTEUR/j);
        position.y=0;
        SDL_FillRect(colonnes[y],NULL,SDL_MapRGB(ecran->format, 0, 0, 0));
        SDL_BlitSurface(colonnes[y],NULL, ecran, &position);
    }

    for (x = 0 ; x <= i ; x++){
        SDL_FreeSurface(lignes[x]); // On libere la mémoire allouée aux cases
    }
    for(y=0;y<=j;y++){
        SDL_FreeSurface(colonnes[y]);
    }

}


int renduGraphique(){
    SDL_Surface *ecran = NULL; // Le pointeur qui va stocker la surface de l'écran
    SDL_Init(SDL_INIT_VIDEO);

    ecran = SDL_SetVideoMode(LARGEUR, HAUTEUR, 32, SDL_HWSURFACE); // On tente d'ouvrir une fenêtre
    if (ecran == NULL) // Si l'ouverture a échoué, on écrit l'erreur et on arrête
    {
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_WM_SetCaption("MorpOthello", NULL);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    dessinePlateau(10,15,ecran);
    SDL_Flip(ecran);
    pauseEcran();

    SDL_Quit();

    return EXIT_SUCCESS;
}

