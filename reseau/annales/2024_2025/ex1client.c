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
//prototypes pr pas avoir de lignes rouges

void requete(int sock, resa r){
    uint8_t buf[6];
    uint32_t l1 = r.jour;
    l1 = (l1<<5) | r.heure;
    l1 = (l1<<6) | r.minute;
    l1 = (l1<<3) | r.duree;
    l1 = (l1<<6) | r.semaine;
    l1 = (l1<<4) | r.repetition;
    l1 = (l1<<5);
    l1 = htonl(l1);
    memcpy(buf, &l1, 4);
    buf[4] = r.effectif;
    buf[5] = r.id;
    send(sock, buf, 6, 0);
}

int main(){
    //étape 1: se connecter à resa.univ-diderot.fr sur le port 1212
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    struct addrinfo *r, *p;
    getaddrinfo("resa.univ-diderot.fr", "1212", &hints, &r);
    int sock;
    p = r;
    while( p != NULL ){
        if((sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) > 0){
            if(connect(sock, p->ai_addr, p->ai_addrlen) == 0){
                break;
            }
            close(sock);
        }
        p = p->ai_next;
    }
    if(r){
        freeaddrinfo(r);
    }
}