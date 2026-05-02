#include <errno.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char **argv){
    int sock = socket(PF_INET6, SOCK_DGRAM, 0);
    struct sockaddr_in6 adr;
    memset(&adr, 0, sizeof(adr));
    inet_pton(AF_INET6, "fdc7:9dd5:2c66:be86:7e57:58ff:fe68:aea9", &adr.sin6_addr);
    adr.sin6_port = htons(7777);
    socklen_t len = sizeof(adr);
    char buf[1024];
    snprintf(buf, 1024, "%s", argv[1]);
    sendto(sock, buf, strlen(buf), 0, (struct sockaddr*)&adr, len);
    char bufrec[16];
    int rec = recvfrom(sock, bufrec, 16, 0, NULL, NULL);
    if(rec == 3){
        exit(0);
    }
    uint16_t taille_max;
    uint32_t nb;
    memcpy(&taille_max, bufrec+2, sizeof(taille_max));
    memcpy(&nb, bufrec+2, sizeof(nb));
    char buffer[taille_max];
    creer_fic(argv[1]);
    for(int i = 0; i< htonl(nb); i++){
        recvfrom(sock, buffer, taille_max, 0, NULL, NULL);
        texte_append(argv[1], buffer, i, taille_max) ;
    }
    exit(0);
}