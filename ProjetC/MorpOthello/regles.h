#ifndef REGLES_H
#define REGLES_H

int alignement(int idepart, int jdepart, int iarrivee, int jarrivee);
int alignementVertical(int idepart, int iarrivee, int j);
int alignementHorizontal(int jdepart, int jarrivee, int i);
int alignementDiagonale1(int idepart, int jdepart, int iarrivee, int jarrivee);
int alignementDiagonale2(int idepart, int jdepart, int iarrivee, int jarrivee);
void convertir(int i, int j);
int win(int i, int j, int *x, int *y);
int coupValide(int i, int j);
int coupEnDehors(int i, int j);
int changerCouleur(int i, int j, int ivoisin, int jvoisin, char couleur, char adversaire);
#endif

