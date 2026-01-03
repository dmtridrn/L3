#include <stdio.h>   // Pour printf() : afficher les messages de joie ou de dépit.
#include <stdlib.h>  // Pour exit(), rand() et srand() : gérer la fin des processus et l'aléatoire.
#include <unistd.h>     // L'include fondamental pour Unix : fork(), pipe(), read(), write() et close().
#include <sys/types.h>  // Définit des types comme pid_t (essentiel pour stocker les IDs des processus).
#include <sys/wait.h>   // Pour wait() ou waitpid() : le père doit attendre que ses fils finissent avant de mourir.
#include <signal.h>     // Crucial ici pour le "coup de sifflet" : envoyer et intercepter des signaux (SIGUSR1 ou SIGINT).
#include <time.h>   
#include <string.h>


/*
int ma(){
    for(int i = 1; i<4; i++){
        if(fork() == 0) { printf("%d... ", i); exit(0); }
        wait(NULL);
    }
    printf("partez ! \n");
}

int mai(){
    int tubes[3][2];
    for(int i = 1; i<4; i++){
        pipe(tubes[i-1]);
        if(fork() == 0) {
            close(tubes[i-1][1]);
            char buf[1];
            read(tubes[i-1][0], buf, 1);
            printf("%d... ", i); exit(0); 
        }
        close(tubes[i-1][0]);
    }
        write(tubes[2][1], "a", 1);
        wait(NULL);
        write(tubes[1][1], "a", 1);
        wait(NULL);
        write(tubes[0][1], "a", 1);
        wait(NULL);
    printf("partez ! \n");
}
*/

sig_atomic_t flag = 4;

void handler(int sig){
    if(sig == SIGUSR1){
        flag--;
    }
}

int main(){
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handler;
    sigaction(SIGUSR1, &sa, NULL);

    for(int i = 1; i<4; i++){
        if(fork() == 0) { 
            while(flag != i){
                pause();
            }
            printf("%d... ", i); 
            exit(0); 
        }
    }
    for(int i = 0; i<3; i++){
        kill(-getpid(), SIGUSR1);
        wait(NULL);
    }
    printf("partez ! \n");
}

