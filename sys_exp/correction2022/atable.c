#include <stdio.h>      // Pour printf()
#include <stdlib.h>     // Pour exit(), rand() et srand()
#include <unistd.h>     // Pour fork(), getpid(), sleep() et pause()
#include <signal.h>     // Pour kill() et signal() ou sigaction()
#include <sys/types.h>  // Pour le type pid_t
#include <sys/wait.h>   // Pour wait() (nettoyage des processus fils)
#include <time.h>       // Pour time() afin d'initialiser le générateur aléatoire
#include <string.h>

volatile sig_atomic_t flag = 0;

void sighandle(int sig){
    if(sig == SIGUSR1){
        flag = 1;
    }
}

int main(){
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = sighandle;
    sigaction(SIGUSR1, &sa, NULL);
    pid_t pid;
    for(int i = 0; i<10; i++){
        pid = fork();
        if(pid == 0){
            while(flag == 0){
                pause();
            }
            srandom(time(NULL) ^ (getpid() << 8)); 
            int temp = random() % 6;
            sleep(temp);
            printf("oui jrrv papa je suis %d\n", getpid());
            exit(0);
        }
    }
    if(pid){
        srandom(time(NULL) ^ (getpid() << 8)); 
        int temps = random() % 11;
        printf("je prépare a graille les gosses\n");
        sleep(temps);
        printf("ATABLE!!!!\n");
        kill(-getpid(), SIGUSR1);
        for(int i = 0; i<10; i++){
            pid_t mort = wait(NULL);
            printf("enfin petit %d \n", mort);
        }
    }
}