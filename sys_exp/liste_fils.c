#include <stdio.h>      // Pour printf, perror, snprintf
#include <stdlib.h>     // Pour exit, malloc, free, atoi
#include <unistd.h>     // Pour fork, pipe, execvp, dup2, read, close
#include <sys/types.h>  // Pour le type pid_t
#include <sys/wait.h>   // Pour waitpid
#include <string.h>     // Pour strtok, strcat, strlen (parsing des PIDs)
#include <errno.h>      // Pour la gestion fine des erreurs système

int main(int argc, char **argv){
    int tube[2];
    pipe(tube);

    pid_t pid = fork();
    if(pid == 0){
        close(tube[0]);
        dup2(tube[1], STDOUT_FILENO);
        execlp("ps", "ps", "-ppid", argv[1], "-opid=", NULL);
    }
    else{
        close(tube[1]);
        char buf[4096];
        wait(NULL);
        int r = read(tube[0], buf, 4096);
        while(r > 0){
            for(int i = 0; i<r; i++){
                if(buf[i] == '\n'){
                    buf[i] = ' ';
                }
            }
            buf[r] = '\0';
            printf("%s", buf);
            if (fork() == 0){
                close(tube[0]);
                dup2(tube[1], STDOUT_FILENO);
                execlp("ps", "ps", "-ppid", buf, "-opid=", NULL);
            }
            else{
                r = read(tube[0], buf, 4096);
                wait(NULL);
            }
        }
    }
}