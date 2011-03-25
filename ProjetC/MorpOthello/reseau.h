#ifndef RESEAU_H
#define RESEAU_H
typedef int SOCKET;

void serverSide();
void clientSide();
void playClient();
void playServer();
int actionToDo(int i,SOCKET sock);


#endif
