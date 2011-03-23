#ifndef REGLES_H
#define REGLES_H

void convertir(int i, int j);
int win(int i, int j, int *x, int *y);
int coupValide(int i, int j);
int coupEnDehors(int i, int j);
int changerCouleur(int i, int j, int ivoisin, int jvoisin, char couleur, char adversaire);
#endif

