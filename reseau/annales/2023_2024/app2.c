#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>

#define BUF_SIZE 1024

struct arg {int sock; int *flag; pthread_mutex_t *verrou};

void prepa_recept(int sock) {
    struct sockaddr_in6 adr = {AF_INET6, htons(1212), 0, IN6ADDR_ANY_INIT, 0};
    bind(sock, (struct sockaddr *)&adr, sizeof(adr));
    struct ipv6_mreq mreq;
    inet_pton(AF_INET6, "ff12::ae2:b", &mreq.ipv6mr_multiaddr);
    mreq.ipv6mr_interface = 0;
    setsockopt(sock, IPPROTO_IPV6, IPV6_JOIN_GROUP, &mreq, sizeof(mreq));
}

int prepa_env_recept(char *h, char *p){
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET6;
    hints.ai_socktype = SOCK_STREAM;
    struct addrinfo *r, *c;
    if ((getaddrinfo(h, p, &hints, &r)) != 0) exit(EXIT_FAILURE);
    int sock;
    c = r;
    while( c != NULL ){
        if((sock = socket(c->ai_family, c->ai_socktype, c->ai_protocol)) > 0){
            if(connect(sock, c->ai_addr, c->ai_addrlen) == 0){
                break;
            }
            close(sock);
        }
        c = c->ai_next;
    }
    freeaddrinfo(r);
    return sock;
}

void *jeu(void *args){
    struct arg a = *((struct arg *)args);
    int s = a.sock;
    int *flag = a.flag;
    pthread_mutex_t *verrou = a.verrou;
    char calcul[] = "37x45+12";
    int res;
    send(s, calcul, strlen(calcul), 0);
    recv(s, &res, sizeof(res), 0);
    pthread_mutex_lock(verrou);
    if(*flag){
        char env[] = "g";
        send(s, env, 1, 0);
        pthread_mutex_unlock(verrou);
        pthread_exit(NULL);
    }
    char env[] = "p";
    send(s, env, 1, 0);
    printf("%d\n", ntohl(res));
}

int main(int argc, char const *argv[]) {
    int sock1 = socket(AF_INET6, SOCK_DGRAM, 0);
    //prepare sock1 pour la reception du 1er message de l'application 1
    prepa_recept(sock1);
    char buf1[BUF_SIZE];
    memset(buf1, 0, sizeof(buf1));
    int lu=read(sock1, buf1, BUF_SIZE);

    int s1 = socket(AF_INET6, SOCK_DGRAM, 0);
    //prepare sock1 pour la reception du 1er message de l'application 1
    prepa_recept(s1);
    char buf2[BUF_SIZE];
    memset(buf2, 0, sizeof(buf2));
    int lu=read(s1, buf2, BUF_SIZE);

    pthread_t t1,t2;

    int sock2 = prepa_env_recept(buf1, memchr(buf1, '\0', lu) +1);
    int sock3 = prepa_env_recept(buf2, memchr(buf2, '\0', lu) +1);
    pthread_mutex_t verrou = PTHREAD_MUTEX_INITIALIZER;
    int flag = 1;
    struct arg a1 = {sock2, &flag};
    struct arg a2 = {sock3, &flag};

    pthread_create(&t1, NULL, jeu, &a1);
    pthread_create(&t2, NULL, jeu, &a2);

    close(sock1);
    return 0;
}