#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <poll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int fic_existe(char *nomfic);
int fic_taille(char *nomfic);
int lire_fic(char *nomfic, char *buf, int i, int tmax);
void mess_num(int nb, char *mess);

int main(){
    int sock = socket(AF_INET6, SOCK_DGRAM, 0);
    struct sockaddr_in6 adr;
    adr.sin6_family = AF_INET6;
    adr.sin6_port = htons(7777);
    adr.sin6_addr = in6addr_any;
    bind(sock, (struct sockaddr *)&adr, sizeof(adr));

    char bufrec[1024];

    struct sockaddr_in6 adrclient;
    socklen_t len = sizeof(adr);
    int r = recvfrom(sock, bufrec, 1024, 0, (struct sockaddr *)&adrclient, &len);
    bufrec[r] = '\0';
    char header[8];
    if(fic_existe(bufrec) == 0){
        char buf[3] = "NOK";
        sendto(sock, buf, 3, 0, (struct sockaddr *)&adrclient, sizeof(adrclient));
        close(sock);
        exit(0);
    }
    int taille = fic_taille(bufrec);
    uint16_t taille_max = 1400;
    uint32_t nb = (taille + taille_max - 1) / taille_max;
    taille_max = htons(taille_max);
    nb = htonl(nb);
    memcpy(header, "OK", 2);
    memcpy(header+2, &taille_max, 2);
    memcpy(header+4, &nb, 4);
    sendto(sock, header, 8, 0, (struct sockaddr *)&adrclient, sizeof(adrclient));

    char bufenv[taille_max+4];

    struct pollfd fds;
    fds.fd = sock;
    fds.events = POLLIN;
    bufrec[1] = 'a'; //pour le atoi
    for(int i = 0; i < nb; i++){
        int l = lire_fic(bufrec, bufenv, i, taille_max+4);
        mess_num(i, bufenv);
        sendto(sock, bufenv, l, 0, (struct sockaddr *)&adrclient, sizeof(adrclient));
        if(poll(&fds, 1, 0) > 0){
            recvfrom(sock, bufrec, 1, 0, NULL,NULL);
            //on renvoie le paquet nb = atoi(bufrec)
            int paquet = atoi(bufrec);
            l = lire_fic(bufrec, bufenv, paquet, taille_max+4);
            sendto(sock, bufenv, l, 0, (struct sockaddr *)&adrclient, sizeof(adrclient));
        }
    }
    if(poll(&fds, 1, 5000) > 0){
            recvfrom(sock, bufrec, 1, 0, NULL,NULL);
            //on renvoie le paquet nb = atoi(bufrec)
            int paquet = atoi(bufrec);
            int o = lire_fic(bufrec, bufenv, paquet, taille_max+4);
            sendto(sock, bufenv, o, 0, (struct sockaddr *)&adrclient, sizeof(adrclient));
        }
    close(sock);
    exit(0);
}