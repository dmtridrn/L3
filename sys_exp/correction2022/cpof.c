#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>


int main(int argc, char **argv){
    const char *chemin = argv[1];
    int tube[2];
    pipe(tube);
    pid_t pid = fork();
    if(pid == 0){
        close(tube[0]);
        dup2(tube[1], STDOUT_FILENO);
        execlp("lsof", "lsof", "-t", chemin, NULL);
    }
    else{
        close(tube[1]);
        char buf[1024];
        int r;
        while((r = read(tube[0], buf, sizeof(buf)))){
            buf[r] = '\0';
            printf("%s", buf);
        }
        wait(NULL);
    }
    return 0;
}