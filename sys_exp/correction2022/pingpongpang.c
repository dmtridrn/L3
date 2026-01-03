#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

sig_atomic_t flag = 0;

void signahandle(int sig){
    flag ++;
}

int main() {
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = signahandle;
    sigaction(SIGUSR1, &sa, NULL);
    pid_t pid = fork();
    if(pid == 0){
        sa.sa_handler = signahandle;
        sigaction(SIGUSR1, &sa, NULL);
        printf("ping ");
        fflush(stdout);
        kill(getppid(), SIGUSR1);
        while(flag != 1) pause();
        printf("pang ");
        fflush(stdout);
        exit(0);
    }
    else{
        while(flag != 1) pause();
        printf("pong ");
        fflush(stdout);
        kill(pid, SIGUSR1);
        wait(NULL);
        exit(0);
    }
}