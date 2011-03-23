#include <stdio.h>
#include <string.h>
#include "globals.h"
#include <unistd.h>

/*boucle principale*/
int main(int argc, char ** argv)
{
    while(1){
        int pid=fork();
        if(pid==0){
            renduGraphique();
        }
        else{
            lancerMenu();
        }
    }
    return 0;
}
