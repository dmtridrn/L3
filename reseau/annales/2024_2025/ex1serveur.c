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

struct resa { uint8_t jour, heure, minute, duree, semaine, repetition, effectif, id; } typedef resa;
struct arg { int sock; pthread_mutex_t *verrou } typedef arg;
int req_resa(struct resa r);
char* info_salle(int num);
int faire_resa(int num, struct resa r);
int oter_resa(int num, struct resa r);

resa req_client(int sock){
    uint8_t buff[6];
    resa renv;
    int total = 0;
    int lus = 0;
    while(total < 6){
        lus = recv(sock, buff+total, 6-total, 0);
        total+=lus;
    }
    uint32_t l1;
    memcpy(&l1, buff, 4);
    l1 = ntohl(l1);
    renv.repetition = (l1>>5) & ((1<<4)-1);
    renv.semaine = (l1>>9) & ((1<<6)-1);
    renv.duree = (l1>>15) & ((1<<3)-1);
    renv.minute = (l1>>18) & ((1<<6)-1);
    renv.heure = (l1>>24) & ((1<<5)-1);
    renv.jour = (l1>>29) & ((1<<3)-1);
    memcpy(&renv+4, buff+4, 2);
    return renv;
}

void resa_client(int sock, resa res, pthread_mutex_t *verrou){
    pthread_mutex_lock(verrou);
    int salle = req_resa(res);
    if(salle > 0){
        faire_resa(salle, res);
        pthread_mutex_unlock(verrou);
        char *infos = info_salle(salle);
        send(sock, infos, strlen(infos), 0);
        free(infos);
    }
    if(salle == 0){
        pthread_mutex_unlock(verrou);
        char buff[6] = "NORESA";
        send(sock, buff, sizeof(buff), 0);
    }
    shutdown(sock, SHUT_WR);
    char buffrec[3];
    int total = 0;
    while(total < 3){
        int lus = recv(sock, buffrec, 3-total, 0);
        if(lus == 0){
            close(sock);
            pthread_exit(NULL);
        }
        total+=lus;
    }
    char buffok[3] = "RNO";
    if(memcmp(buffrec, buffok, 3) == 0){
        pthread_mutex_lock(verrou);
        int i = oter_resa(salle, res);
        pthread_mutex_unlock(verrou);
    }
    close(sock);
    pthread_exit(NULL);
    return;
}

void *thr(void *args){
    arg *a = (arg *)args;
    int sock_client = a->sock;
    pthread_mutex_t *verrou = a->verrou;
    free(args);
    resa r = req_client(sock_client);
    resa_client(sock_client, r, verrou);
    return NULL;
}

int main(){
    int sock = socket(AF_INET6, SOCK_STREAM, 0);
    struct sockaddr_in6 adrsock;
    memset(&adrsock, 0, sizeof(adrsock));
    adrsock.sin6_family = AF_INET6;
    adrsock.sin6_port = htons(1212);
    adrsock.sin6_addr = in6addr_any;
    bind(sock, (struct sockaddr *)&adrsock, sizeof(adrsock));
    pthread_mutex_t verrou = PTHREAD_MUTEX_INITIALIZER;
    listen(sock, 5);
    while(1){
        arg* a = malloc(sizeof(arg));
        a->sock = sock;
        a->verrou = &verrou;
        int s = accept(sock, NULL, NULL);
        pthread_t thread;
        pthread_create(&thread, NULL, thr, a);
        pthread_detach(thread);
    }
}