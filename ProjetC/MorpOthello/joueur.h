#ifndef JOUEUR_H
#define JOUEUR_H
/****

Definition du joueur


****/


typedef struct joueur {
    char name[256];
    char couleur;
    int score;
    int partiesGagnees;
    int partiesPerdues;
}Joueur;

void init2Joueur(char * name1,char * name2,int tournoi);
Joueur verifiCreationJoueur(char * name);

#endif
