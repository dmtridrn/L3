#include <stdio.h>      // Pour printf et dprintf
#include <stdlib.h>     // Pour exit() et la gestion mémoire
#include <dirent.h>     // Pour opendir(), readdir() et closedir()
#include <sys/types.h>  // Pour les types système (pid_t, mode_t)
#include <sys/stat.h>   // Pour stat(), lstat() et les macros S_ISLNK/S_ISDIR
#include <unistd.h>     // Pour readlink()
#include <string.h>     // Pour strcmp() (filtrage de "." et "..") et snprintf
#include <limits.h>     // Pour la constante PATH_MAX
#include <errno.h>      // Pour analyser pourquoi stat() ou opendir() échoue


void parcours(char *racine){
    char *basepath = racine;
    struct dirent *entry;
    DIR *dirp = opendir(basepath);
    struct stat st;
    while((entry = readdir(dirp))){
        if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0){
            continue;
        }
        char path[PATH_MAX];
        memset(path, 0, PATH_MAX);
        snprintf(path, PATH_MAX, "%s/%s", basepath, entry->d_name);
        lstat(path, &st);
        if(S_ISLNK(st.st_mode)){
            struct stat lst;
            if(stat(path, &lst) == -1){
                char link[PATH_MAX];
                ssize_t len = readlink(path, link, PATH_MAX);
                path[len] = '\0';
                printf("lien corrompu: %s -> %s",path, link);
            }
        }
        else if(S_ISDIR(st.st_mode)){
            parcours(path);
        }
    }
    closedir(dirp);
}

int main(int argc, char **argv){
}

