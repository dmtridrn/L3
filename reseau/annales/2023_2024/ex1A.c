#include <stdio.h>      // Pour printf, sprintf, scanf
#include <stdlib.h>     // Pour exit, atoi, malloc
#include <string.h>     // Pour memset, memcpy, strlen, memcmp
#include <unistd.h>     // Pour close, read, write, fork
#include <sys/types.h>  // Pour les types comme pid_t ou size_t
#include <sys/socket.h> // Pour socket, bind, connect, recv, send
#include <arpa/inet.h>  // Pour inet_pton, htons, ntohl
#include <netinet/in.h> // Pour les structures sockaddr_in6
#include <fcntl.h>      // Pour open et les flags comme O_RDONLY
#include <stdint.h>     // Pour uint32_t, uint16_t (très important pour le format réseau)

int cree_fic(char *nomfic);
int texte_append(char *nomfic, char *texte, int i, int tmax);

int main(int argc, char **argv){
    int sock = socket(AF_INET6, SOCK_DGRAM, 0);
    struct sockaddr_in6 adr;
    adr.sin6_family = AF_INET6;
    adr.sin6_port = htons(7777);
    inet_pton(AF_INET6, "fdc7:9dd5:2c66:be86:7e57:58ff:fe68:aea9", &adr.sin6_addr);
    socklen_t len = sizeof(adr);

    sendto(sock, argv[1], strlen(argv[1]), 0, (struct sockaddr *)&adr, sizeof(adr));

    char buf[8];
    recvfrom(sock, buf, 8, 0, NULL, NULL);

    if(buf[0] == 'N'){
        close(sock);
        exit(0);
    }
    uint16_t taille_max;
    uint32_t nb;
    memcpy(&taille_max, buf+2, 2);
    memcpy(&nb, buf+4, 4);
    taille_max = ntohs(taille_max);
    nb = ntohl(nb);

    cree_fic(argv[1]);
    char bufrec[taille_max+1];

    for(int i = 0; i < nb; i++){
        int r = recvfrom(sock, bufrec, taille_max, 0, (struct sockaddr *)&adr, &len);
        bufrec[r] = 0;
        texte_append(argv[1], bufrec, i, taille_max);
    }
    close(sock);
    exit(0);
}