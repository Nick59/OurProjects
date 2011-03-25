#ifndef JEU_H
#define JEU_H

void affectJoueur(Joueur b);
int saisie(int *x, int *y);
void switchJoueur();
int manche();
void afficherPoints();
Joueur partie(int tournoi);
void tournoi();
void lancerMenu();

#endif
