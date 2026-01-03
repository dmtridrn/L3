#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int nettoie(const char *path) {
    DIR *dir = opendir(path);
    if (!dir) {
        return 0; 
    }

    struct dirent *entry;
    struct stat st;
    int peut_etre_supprime = 1;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char nvpath[PATH_MAX];
        snprintf(nvpath, sizeof(nvpath), "%s/%s", path, entry->d_name);

        if (lstat(nvpath, &st) == -1) continue;

        if (S_ISDIR(st.st_mode)) {
            if (nettoie(nvpath) == 0) {
                peut_etre_supprime = 0;
            }
        } 
        else if (S_ISREG(st.st_mode)) {
            if (st.st_size == 0) {
                unlink(nvpath);
            } else {
                peut_etre_supprime = 0;
            }
        } else {
            peut_etre_supprime = 0;
        }
    }

    closedir(dir);


    if (peut_etre_supprime && strcmp(path, ".") != 0) {
        if (rmdir(path) == 0) {
            return 1;
        }
    }

    return 0;
}

int main(int argc, char **argv) {
    const char *target = (argc > 1) ? argv[1] : ".";
    nettoie(target);
    return 0;
}