#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void parcours(char *path){
    DIR *dir = opendir(path);
    struct dirent *entry;
    char fullpath[PATH_MAX];
    while((entry = readdir(dir))){
        if(!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")){
            continue;
        }
        snprintf(fullpath, "%s/%s", path, entry->d_name);
        struct stat st;
        lstat(fullpath, &st);
        if(S_ISDIR(st.st_mode)){
            parcours(fullpath);
        }
        if(S_ISLNK(st.st_mode)){
            if(stat(fullpath, &st) != 0){
                char dest[PATH_MAX];
                int r = readlink(fullpath, dest, sizeof(dest));
                dest[r] = '\0';
                printf("Lien corrompu: %s -> %s\n", fullpath, dest);
            }
        }
    }
    closedir(dir);
}

int main(){
    parcours(".");
}