#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <time.h>
#include <fcntl.h>

    struct arg{int n; pthread_mutex_t *verrou;};


void *fa(void *args) {
    struct arg p = *(struct arg *)args;
    int n = p.n;
    pthread_mutex_t *verrou = p.verrou;
    for(int i=0; i<3; i++)
        n = n * (log(n)+1);
    pthread_mutex_lock(verrou);
    int fd = open("fic.txt", O_WRONLY|O_CREAT|O_APPEND, 0600);
    write(fd, &n, sizeof(double));
    close(fd);
    pthread_mutex_unlock(verrou);
    return NULL;
}

void *fb(void *args) {
    struct arg p = *(struct arg *)args;
    int n = p.n;
    pthread_mutex_t *verrou = p.verrou;
    for(int i=0; i<3; i++)
        n = n + (exp(n)+1);
    pthread_mutex_lock(verrou);
    int fd = open("fic.txt", O_WRONLY|O_CREAT|O_APPEND, 0600);
    write(fd, &n, sizeof(double));
    close(fd);
    pthread_mutex_unlock(verrou);
    return NULL;
}

int main() {
    int sock=socket(PF_INET,SOCK_DGRAM,0);

    struct sockaddr_in adrsock;
    memset(&adrsock, 0, sizeof(adrsock));
    adrsock.sin_family = AF_INET;
    adrsock.sin_port = htons(1234);
    adrsock.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(sock,(struct sockaddr *)&adrsock,sizeof(struct sockaddr_in));

    int n;
    pthread_mutex_t verrou;
    pthread_mutex_t *ptv = &verrou;
    pthread_t thread;
    struct arg a = {n, ptv};
    recvfrom(sock, &n, sizeof(n), 0, NULL, NULL);
    n = ntohl(n);
    if(n > 0)
        pthread_create(&thread, NULL, fa , &a);
    else
        pthread_create(&thread, NULL, fb , &a);
    return 0;
}