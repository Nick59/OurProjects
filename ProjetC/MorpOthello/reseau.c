#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
#include "globals.h"
#include "reseau.h"
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;
int typegame = 0;
SOCKET csock;
SOCKET sock;


/* Ceci est la partie serveur */

void serverSide(){
    printf("Serveur créé, en attente de l'adversaire...\n");
     /* Socket et contexte d'adressage du serveur */
    SOCKADDR_IN sin;
    /*SOCKET sock;*/

    /* Socket et contexte d'adressage du client */
    SOCKADDR_IN csin;
    /*SOCKET csock;*/
    socklen_t crecsize = sizeof(csin);


    /* SERVEUR */
    /*creer une stocket mode tpc ip */
    sock = socket (AF_INET, SOCK_STREAM, 0);

    /*on assigne le port d'ecoute*/
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(9875);

    /*association les infos a la socket*/
    bind(sock, (SOCKADDR*)&sin, sizeof(sin));

    /*etat d'ecoute*/
    listen(sock, 5);

    /*acceptation des clients*/
     csock = accept(sock, (SOCKADDR*)&csin, &crecsize);
     printf("Un client s'est connecté !\n");

    playServer(csock);

    /*ferme les sockets*/
    closesocket (sock);
    closesocket (csock);
}

void clientSide(){
    char choixip [20];
    char* ip;
    printf("Bonjour, veuillez entrer s'il vous plait l'ip du serveur :\n");
    scanf("%s",&choixip);
    int len = strlen(choixip);
    ip = (char*) malloc(sizeof(char)*len);
    strncpy(ip,choixip,len);
    printf("%s\n",ip);
    /*SOCKET sock;*/
    SOCKADDR_IN sin;

     /* Création de la socket */
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

    /* Configuration de la connexion */
    sin.sin_addr.s_addr = inet_addr(ip);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(9875);

    if(connect(sock, (SOCKADDR*)&sin, sizeof(sin)) != SOCKET_ERROR){
        printf("Client connecté, yeah man !\n");
    }else{
        printf("Connexion Impossible, you suck\n");
    }

    playClient(sock);

    closesocket (sock);
}

void playServer(SOCKET csock){
    typegame = 2;
    char j1[256];
    char j2[256];
    printf("Bienvenue, joueur 1 entrez votre nom\n");
    scanf("%s",j1);

    char buffer[256] = "Bienvenue, Joueur 2 entrez votre nom";
    send(csock, buffer, 256,0);
    recv(csock,&j2,256,0);

    printf("Initialisation des Joueurs %s, %s\n",j1,j2);
    init2Joueur(j1,j2,0);
    printf("Initialisation du plateau\n");
    initPlateau();
    printf("Envoi du plateau\n");
    send(csock,&p,sizeof(p),0);
    printf("Envoi du J1\n");
    send(csock,&jo1,sizeof(jo1),0);
    printf("Envoi du J2\n");
    send(csock,&jo2,sizeof(jo2),0);
    printf("Fin d'envoie des données.\n");

    /* Le jeu commence */
    partie(0);
}

void playClient(){
    typegame = 1;
    char buffer[256];
    char j2[256];
    printf("Le joueur 1 saisie sont nom.. Wait please\n");
    recv(sock, buffer, 256, 0);
    printf("Recu : %s\n", buffer);
    /*le joueur entre son nom*/
    scanf("%s",j2);
    send(sock,j2,256,0);
    /*init du plateau et des joueurs */
    recv(sock,&p,sizeof(p),0);
    recv(sock,&jo1,sizeof(jo1),0);
    recv(sock,&jo2,sizeof(jo2),0);

    /* le jeu commence */
    end = 1
    while(!end){

    }

}

void actionToDo(int i){
    switch(i){
        /*demande de coordonées et envoie vers le serveur*/
        case 1:
            int x,y;
            printf("Saisir la ligne\n");
            scanf("%d", x);
            printf("Saisir la colonne\n");
            scanf("%d", y);
            fflush(stdin);
            send(sock,x,sizeof(int),0);
            send(sock,y,sizeof(int),0);
            break;
        /*recuperation du tableau.   */
        case 2:
            recv(sock,&p,sizeof(p),0);
            affichage();
            break;

        default:
            printf("paquet non compris \n");
            break;
    }

}
