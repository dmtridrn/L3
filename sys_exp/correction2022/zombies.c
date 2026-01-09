#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

int main(){
    if(fork()){
        wait(NULL);
        sleep(10);
    }
    else{
        if(fork() && fork() && fork() && fork()){
            sleep(7);
            for(int i = 0; i<4; i++){
                wait(NULL);
            }
        }
        else{
            execlp("sleep", "sleep", "1", NULL);
        }
    }
}
