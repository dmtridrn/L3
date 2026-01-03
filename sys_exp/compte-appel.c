#include <stdio.h>      // Limité à perror() et l'affichage final (printf)
#include <stdlib.h>     // Pour exit()
#include <unistd.h>     // Pour fork(), pipe(), dup2(), execvp(), read(), close()
#include <fcntl.h>      // Pour open() et O_WRONLY (redirection vers /dev/null)
#include <sys/types.h>  // Pour pid_t
#include <sys/wait.h>   // Pour wait()
#include <errno.h> 
#include <string.h>      // Pour la gestion fine des erreurs

int main(int argc, char **argv){
    int fd_null = open("/dev/null", O_WRONLY);
    int tube[2];
    pipe(tube);
    if(fork() == 0){
        dup2(fd_null, STDOUT_FILENO);
        dup2(tube[1], STDERR_FILENO);
        close(tube[0]);
        close(tube[1]);
        close(fd_null);
        argv[0] = "strace";
        execvp("strace", argv);
    }
    close(tube[1]);
    char buffer[1024];
    int n, nb_appels = 0;
    while ((n = read(tube[0], buffer, sizeof(buffer))) > 0) {
        for (int i = 0; i < n; i++) {
            if (buffer[i] == '\n') nb_appels++;
        }
    }
    wait(NULL);
    printf("nombre d'appels: %d\n", nb_appels-1);
    exit(0);
}