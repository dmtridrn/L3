#include <stdio.h>      // Limité à perror() et l'affichage final (printf)
#include <stdlib.h>     // Pour exit()
#include <unistd.h>     // Pour fork(), pipe(), dup2(), execvp(), read(), close()
#include <fcntl.h>      // Pour open() et O_WRONLY (redirection vers /dev/null)
#include <sys/types.h>  // Pour pid_t
#include <sys/wait.h>   // Pour wait()
#include <errno.h> 
#include <string.h>      // Pour la gestion fine des erreurs

int main(int argc, char **argv){
    int tube[2];
    pipe(tube);
    if(fork() == 0){
        int fd_null = open("/dev/null", O_WRONLY);
        dup2(fd_null, STDOUT_FILENO);
        dup2(tube[1], STDERR_FILENO);
        close(tube[1]);
        close(tube[0]);
        close(fd_null);
        argv[0] = "strace";
        execvp("strace", argv);
    }
    close(tube[1]);
    char buf[4096];
    int cpt = 0;
    int n = 0;
    while((n = read(tube[0], buf, sizeof(buf))) > 0){
        for(int i = 0; i<n; i++){
            if(buf[i] == '\n') cpt ++;
        }
    }
    close(tube[0]);
    wait(NULL);
    printf("%d\n", cpt-1);
    exit(0);
}