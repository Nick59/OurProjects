#ifndef GESTION_FICHIERS_H
#define GESTION_FICHIERS_H

Joueur recupererJoueur(char * name, char * fichier);
void afficherScores();
int saveJoueur(Joueur j, char * fichier, char * method);
void majJoueur(Joueur j);
void sauvegardeEnCours(Joueur j1, Joueur j2);

#endif
