#include <stdio.h>   // Pour printf() : afficher les messages de joie ou de dépit.
#include <stdlib.h>  // Pour exit(), rand() et srand() : gérer la fin des processus et l'aléatoire.
#include <unistd.h>     // L'include fondamental pour Unix : fork(), pipe(), read(), write() et close().
#include <sys/types.h>  // Définit des types comme pid_t (essentiel pour stocker les IDs des processus).
#include <sys/wait.h>   // Pour wait() ou waitpid() : le père doit attendre que ses fils finissent avant de mourir.
#include <signal.h>     // Crucial ici pour le "coup de sifflet" : envoyer et intercepter des signaux (SIGUSR1 ou SIGINT).
#include <time.h>    // Pour time() : permet d'initialiser srand(time(NULL)) pour que l'aléatoire change à chaque exécution.


int main(int argc, char **argv){

    //init: tableau de fils, tableau de pipe, pipe réponse, indice des fils
    //fp = fils -> pere pf = pere -> fils
    int idx;
    int balle = -1;
    int nbrfils = atoi(argv[1]);
    pid_t tabpid[nbrfils];
    int tubefp[2];
    pipe(tubefp);
    int tubepf[nbrfils][2];
    pid_t pid;
    for(int i = 0; i<nbrfils; i++){
        pipe(tubepf[i]);
        pid = fork();
        if(pid){
            tabpid[i] = pid;
        }
        else{
            idx = i;
        }
    }
    if(pid == 0){
        while(1){
            read(tubepf[idx][0], &balle, sizeof(int));
            write(tubefp[1], &balle, sizeof(int));
            balle = -1;
        }
    }
}