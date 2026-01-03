#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int parcours_rep(char *path){
    int cpt = 0;
    DIR *dir = opendir(path);
    struct dirent *entry;

    struct stat st;
    char nvpath[4096];
    while((entry = readdir(dir))){
        if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;

        snprintf(nvpath, 4096, "%s/%s", path, entry->d_name);

        stat(nvpath, &st);
        if(S_ISDIR(st.st_mode)){
            cpt++;
            cpt += parcours_rep(nvpath);
        }
    }
    return cpt;
}

int main(){
    int cpt = parcours_rep(".");
    printf("il ya %d sous répertoires\n", cpt);
}