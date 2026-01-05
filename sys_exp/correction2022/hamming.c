#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int hamming(int fd1, int fd2){
    int cpt = 0;
    int r1, r2;
    char buf1[4096];
    char buf2[4096];

    while(1){
        r1 = read(fd1, buf1, sizeof(buf1));
        r2 = read(fd2, buf2, sizeof(buf2));
        
        int mini = (r1<r2) ? r1 : r2; 
        for(int i = 0; i<mini; i++){
            if(buf1[i] != buf2[i]){
                cpt ++;
            }
        }
        if(r1 != r2){
            cpt+= abs(r1-r2);
        }
        if(r1 == 0 && r2 == 0) break;
    }
    return cpt;
}

int main(int argc, char **argv){
    int fd1 = open(argv[1], O_RDONLY);
    int fd2 = open(argv[2], O_RDONLY);

    int cpt = hamming(fd1, fd2);
    printf("%d\n", cpt);
    exit(0);

}