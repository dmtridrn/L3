#include <stdio.h>      // Pour printf()
#include <stdlib.h>     // Pour exit(), rand() et srand()
#include <unistd.h>     // Pour fork(), getpid(), sleep() et pause()
#include <signal.h>     // Pour kill() et signal() ou sigaction()
#include <sys/types.h>  // Pour le type pid_t
#include <sys/wait.h>   // Pour wait() (nettoyage des processus fils)
#include <time.h>       // Pour time() afin d'initialiser le générateur aléatoire
#include <string.h>
sig_atomic_t flag = 0;
void sighandler(int sig){
    if(sig == SIGUSR1) flag += 1;
}
int main(){
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = SIG_IGN;
    sigaction(SIGUSR1, &sa, NULL);
    for(int i = 1; i<5; i++){
        if(fork() == 0){
            sa.sa_handler = sighandler;
            sigaction(SIGUSR1, &sa, NULL);
            while(flag != i) pause();
            printf("jrrv\n");
            exit(0);
        }
    }
    srand(time(NULL));
    int attente = random() % 6;
    sleep(attente);
    for(int i = 0; i<4; i++){
        sleep(1);
        printf("à table les peti \n");
        kill(-getpid(), SIGUSR1);
        wait(NULL);
    }
    exit(0);
}