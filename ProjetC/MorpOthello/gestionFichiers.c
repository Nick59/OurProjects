#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"
#include <unistd.h>
#define TAILLE_LIGNE 400

/* Cette fonction retourne le joueur recherché dans users.mpo , ou un joueur nommé "noname" en cas d'echec */
Joueur recupererJoueur(char * name, char * fichier){
    char f[50];
    sprintf(f,"./save/%s.mpo",fichier);
    FILE* users=fopen(f,"r");
    Joueur tmp;
    while(fscanf(users,"%s %c %d %d %d", &tmp.name, &tmp.couleur, &tmp.score, &tmp.partiesGagnees, &tmp.partiesPerdues)!=EOF){
        if(strcmp(name,tmp.name)==0){
            fclose(users);
            return tmp;
        }
    }
    strcpy(tmp.name,"noname");
    fclose(users);
    return tmp;
}

/* Cette fonction enregistre le joueur a la fin du fichier fichier.mpo renvoie 0 si erreur sinon 1 */
int saveJoueur(Joueur j, char * fichier,char * method){
        char f[50];
        sprintf(f,"./save/%s.mpo",fichier);
        FILE* users=fopen(f,method);
        fseek(users, 0, SEEK_END);
    	fprintf(users,"%s %c %d %d %d \n",j.name,j.couleur,j.score,j.partiesGagnees,j.partiesPerdues );
        fclose(users);
        return 1;
}

/* Cette fonction affiche les scores, renvoie 0 si erreur, sinon 1*/
void afficherScores(){
    FILE* users=fopen("./save/users.mpo","r");
    Joueur tmp;
    printf("==Joueur==\t==Parties gagnées==\t==Parties perdues==\n");
    while(fscanf(users,"%s %c %d %d %d", &tmp.name, &tmp.couleur, &tmp.score, &tmp.partiesGagnees, &tmp.partiesPerdues)!=EOF){
        if(strlen(tmp.name)>3){
            printf("==%s==\t            %d \t            %d\n",tmp.name,tmp.partiesGagnees,tmp.partiesPerdues);
        }
        else{
            printf("==%s==\t\t            %d \t            %d\n",tmp.name,tmp.partiesGagnees,tmp.partiesPerdues);
        }
    }
    fclose(users);

}

void majJoueur(Joueur j){
    int pid;
    FILE * users=fopen("./save/users.mpo","r");
    FILE * temp=fopen("./save/temp.mpo","w+");
    Joueur tmp;
    while(fscanf(users,"%s %c %d %d %d", &tmp.name, &tmp.couleur, &tmp.score, &tmp.partiesGagnees, &tmp.partiesPerdues)!=EOF){
        if(strcmp(tmp.name,j.name)==0){
            fprintf(temp,"%s %c %d %d %d\n", j.name, '.', j.score, j.partiesGagnees, j.partiesPerdues);
        }
        else{
            fprintf(temp,"%s %c %d %d %d\n", tmp.name, '.', tmp.score, tmp.partiesGagnees, tmp.partiesPerdues);
        }
    }
    fclose(users);
    fclose(temp);
    system("mv ./save/temp.mpo ./save/users.mpo");
}

void sauvegardeEnCours(Joueur j1, Joueur j2){

    saveJoueur(j1,"partie","w+");
    saveJoueur(j2,"partie","r+");
}
