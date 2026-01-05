#include <stdio.h>   // Pour printf() : afficher les messages de joie ou de dépit.
#include <stdlib.h>  // Pour exit(), rand() et srand() : gérer la fin des processus et l'aléatoire.
#include <unistd.h>     // L'include fondamental pour Unix : fork(), pipe(), read(), write() et close().
#include <sys/types.h>  // Définit des types comme pid_t (essentiel pour stocker les IDs des processus).
#include <sys/wait.h>   // Pour wait() ou waitpid() : le père doit attendre que ses fils finissent avant de mourir.
#include <signal.h>     // Crucial ici pour le "coup de sifflet" : envoyer et intercepter des signaux (SIGUSR1 ou SIGINT).
#include <time.h>
#include <limits.h>

int main(int argc, char **argv){
    int nbfils = atoi(argv[1]);
    int idx;
    pid_t pids[nbfils];
    pid_t pid = 1;
    int tubefp[2];
    pipe(tubefp);
    int tubespf[nbfils][2];
    for(int i = 0; i < nbfils && pid > 0; i++){
        pipe(tubespf[i]);
        pid = fork();
        if(pid == 0){
            idx = i;
            pids[i] == getpid();
            close(tubespf[i][1]);
            close(tubefp[0]);
        }
    }

    if(pid){
        srand(time(NULL));
        int maxi = random() % INT_MAX;
        int valeur = random() % maxi;
        printf(" la valeur secrète est: %d\n", valeur);
        for(int i = 0; i<nbfils; i++){
            write(tubespf[i][1], &maxi, sizeof(int));
        }
        int reponse;
        int candidat;
        int pidrep[2];//[IDX][REPONSE]
        while(reponse != valeur){
            read(tubefp[0], pidrep, 2*sizeof(int));
            reponse = pidrep[1];
            candidat = pidrep[0];
            
        }
    }
}   