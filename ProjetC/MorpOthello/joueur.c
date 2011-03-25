#include "joueur.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"
/* Variables */

Joueur jo1;
Joueur jo2;
Joueur joueurCourant;

/* Cette fonction charge les profils utilisateurs passes en parametres
   Si ils n'existent pas, ils sont créés.
 */
void init2Joueur(char *name1, char *name2, int tournoi)
{
    char nom[256];
    FILE* partie=fopen("./save/partie.mpo","r");
    if(partie!=NULL && !tournoi){
        jo1=recupererJoueur(name1,"partie");
        jo2=recupererJoueur(name2,"partie");
        if(strcmp(jo1.name,"noname")==0 || strcmp(jo2.name,"noname")==0){
            fclose(partie);
            jo1=verifiCreationJoueur(name1);
            jo2=verifiCreationJoueur(name2);
            jo1.couleur='B';
            jo2.couleur='N';
        }
        else{
            fclose(partie);
            partie=fopen("./save/partie.mpo","w+");
        }
    }
    else{
        fclose(partie);
        jo1=verifiCreationJoueur(name1);
        jo2=verifiCreationJoueur(name2);
        jo1.couleur='B';
        jo2.couleur='N';
    }
}

/* verifie l'existence du joueur, si il n'existe pas ,le cree et le sauvegarde */
Joueur verifiCreationJoueur(char * name){
    Joueur j=recupererJoueur(name,"users");
    if(strcmp(j.name,"noname")==0){
        strcpy(j.name,name);
        j.score=0;
        j.couleur='.';
        j.partiesGagnees=0;
        j.partiesPerdues=0;
        saveJoueur(j,"users","r+");
    }
    return j;
}
