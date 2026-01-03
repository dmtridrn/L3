#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

int main(){

    if(fork()){
        wait(NULL);
        sleep(20);
    }
    else{
        if(fork() && fork()){
            sleep(6);
        }
        else{
            if(fork()){
                execlp("sleep", "sleep", "1", NULL);
            }
            else{
                execlp("sleep", "sleep", "7", NULL);
            }
        }
    }
}
