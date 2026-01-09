#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

int man() {
    int tubes[2];
    pipe(tubes);
    if (fork() == 0) {
        int tube[2];
        pipe(tube);
        if (fork() == 0){
            close(tube[1]);
            char buf[100];
            read(tube[0], buf, sizeof(buf));
            printf("ping ");
        }
        else{
            char buf[100];
            close(tubes[1]); close(tube[0]);
            read(tubes[0], buf, 100);
            printf("pong ");
            write(tube[1], "a", 1);
        }
    }
    else{
        if (fork() == 0){
            close(tubes[0]);
            printf("pang ");
            write(tubes[1], "a", 1);
        } 
    }
}

int main(){

}