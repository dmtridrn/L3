#include <stdio.h>      // Pour printf, sprintf, scanf
#include <stdlib.h>     // Pour exit, atoi, malloc
#include <string.h>     // Pour memset, memcpy, strlen, memcmp
#include <unistd.h>     // Pour close, read, write, fork
#include <sys/types.h>  // Pour les types comme pid_t ou size_t
#include <sys/socket.h> // Pour socket, bind, connect, recv, send
#include <arpa/inet.h>  // Pour inet_pton, htons, ntohl
#include <netinet/in.h> // Pour les structures sockaddr_in6
#include <fcntl.h>      // Pour open et les flags comme O_RDONLY
#include <stdint.h>
#include <poll.h>

int fic_existe(char *nomfic);
int fic_taille(char *nomfic);
int lire_fic(char *nomfic, char *buf, int i, int tmax);

int main(){
    int sock = socket(AF_INET6, SOCK_DGRAM, 0);
    struct sockaddr_in6 adr;
    adr.sin6_addr = in6addr_any;
    adr.sin6_port = htons(7777);
    adr.sin6_family = AF_INET6;
    socklen_t len = sizeof(adr);
    bind(sock, (struct sockaddr *)&adr, sizeof(adr));

    char buffrec[256];
    struct sockaddr_in6 client;
    socklen_t lenc = sizeof(client);
    recvfrom(sock, buffrec, sizeof(buffrec), 0, (struct sockaddr *)&client, &lenc);
    if(!fic_existe(buffrec)){
        sendto(sock, "NOK", 3, 0, (struct sockaddr *)&client, lenc);
        close(sock);
        exit(0);
    }
    uint16_t taille_max = 1400;
    int taille = fic_taille(buffrec);
    uint32_t nb = (taille + taille_max - 1) / taille_max;
    taille_max = htons(taille_max);
    nb = htonl(nb);
    char buffenv[8];
    memcpy(buffenv, "OK", 2);
    memcpy(buffenv+2, &taille_max, 2);
    memcpy(buffenv+4, &nb, 4);
    sendto(sock, buffenv, 8, 0, (struct sockaddr *)&client, lenc);
    taille_max = ntohs(taille_max);
    char buffic[taille_max];

    struct pollfd fd;
    fd.events = POLLIN;
    fd.fd = sock;
    uint32_t idx;
    for(int i = 0; i<nb; i++){
        int lus = lire_fic(buffrec, buffic, i, taille_max);
        sendto(sock, buffic, lus, 0, (struct sockaddr *)&client, lenc);
        poll(&fd, 1, 0);
        if(fd.revents & POLLIN){
            recvfrom(sock, &idx, 4, 0, NULL, NULL);
            int lus = lire_fic(buffrec, buffic, nb, taille_max);
            sendto(sock, buffic, lus, 0, (struct sockaddr *)&client, lenc); 
        }
    }

    while(poll(&fd, 1, 50000) > 0){
        recvfrom(sock, &idx, 4, 0, NULL, NULL);
        int lus = lire_fic(buffrec, buffic, nb, taille_max);
        sendto(sock, buffic, lus, 0, (struct sockaddr *)&client, lenc);
    }
    close(sock);
    exit(0);
}