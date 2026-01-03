#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BLOCKSIZE 4096

int my_cp(char *src, char *dst){
    char buf[BLOCKSIZE];
    int fds = open(src, O_RDONLY);
    if(fds < 0) return 1;
    struct stat st;
    if(stat(src, &st) < 0) return 1;
    int fdd = open(dst, O_WRONLY | O_TRUNC | O_CREAT, st.st_mode);
    if(fdd < 0) return 1;

    int r, w;

    while((r = read(fds, buf, BLOCKSIZE))){
        if(r == -1){close(fds); close(fdd); return 1;} 
        w = write(fdd, buf, r);
        if(w == -1){ return 1; close(fds); close(fdd);}
    }
    fchmod(fdd, st.st_mode & 0777);
    close(fds);
    close(fdd);
    return 0;
}

int my_cp_rec (char *src, char *dst){
    char paths[4096], pathd[4096];

    struct stat st;
    stat(src, &st);
    if(S_ISREG(st.st_mode)){
        return my_cp(src, dst);
    }
    else{
        mkdir(dst, st.st_mode & 0777);
        DIR* dir = opendir(src);
        struct dirent *entry;
        while((entry = readdir(dir))){
            if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0){
                continue;
            }

            snprintf(paths, sizeof(paths), "%s/%s", src, entry->d_name);
            snprintf(pathd, sizeof(pathd), "%s/%s", dst, entry->d_name);
            my_cp_rec(paths, pathd);
        }
        closedir(dir);
    }
    return 0;
}

int main(int argc, char **argv){
    return my_cp_rec(argv[1], argv[2]);
}