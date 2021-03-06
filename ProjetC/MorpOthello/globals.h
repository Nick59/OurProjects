#ifndef GLOBALS_H
#define GLOBALS_H

/****

 Fichier header de variables globales

 include le "h" de vos structures ainsi que la variable precedee du mot cle "extern"

 ****/
#include <SDL.h>
#include "regles.h"
#include "joueur.h"
#include "plateau.h"
#include "gestionFichiers.h"
#include "menu.h"
#include "jeu.h"
#include "ia.h"
#include "sdl.h"

extern Joueur jo1;
extern Joueur jo2;
extern Joueur joueurCourant;
extern Plateau p;
extern SDL_Surface *ecranJeu;

#endif
