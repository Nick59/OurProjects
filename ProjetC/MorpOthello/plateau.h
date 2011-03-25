#ifndef PLATEAU_H
#define PLATEAU_H
/****

Definition du plateau


****/

typedef struct plateau {
    char grille[10][15];
}Plateau;

void affect(int i, int j, char val);
void initPlateau();
void affichage();
char getCase(int x, int y);

#endif
