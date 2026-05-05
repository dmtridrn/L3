#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main(){
    //socket réception
    int sock = socket(AF_INET6, SOCK_DGRAM, 0);
    int loop = 1;
    setsockopt(sock, IPPROTO_IPV6, IPV6_MULTICAST_LOOP, &loop, sizeof(loop));
    //adresse réception
    struct sockaddr_in6 serv;
    memset(&serv, 0, sizeof(serv));
    serv.sin6_family = AF_INET6;
    serv.sin6_port = htons(12121);
    serv.sin6_addr = in6addr_any;
    bind(sock, (struct sockaddr *)&serv, sizeof(serv));

    //adresse envoi
    struct sockaddr_in6 addr_envoi;
    memset(&addr_envoi, 0, sizeof(addr_envoi));
    addr_envoi.sin6_family = AF_INET6;
    addr_envoi.sin6_port = htons(10201);
    inet_pton(AF_INET6, "ff02::4:3:2:1", &addr_envoi.sin6_addr);

    while(1){
        struct sockaddr_in6 client;
        socklen_t longu = sizeof(client);
        char adresse[INET6_ADDRSTRLEN];

        char bufrec[1024];
        int lu = recvfrom(sock, bufrec, sizeof(bufrec), 0, (struct sockaddr *)&client, &longu);
        bufrec[lu] = '\0';

        time_t maintenant;
        struct tm *info_temps;
        char chaine_heure[10];
        time(&maintenant);
        info_temps = localtime(&maintenant);

        inet_ntop(AF_INET6, &(client.sin6_addr), adresse, sizeof(adresse));
        int len = strlen(bufrec) + 5 + INET6_ADDRSTRLEN;
        char bufenv[len];
        sprintf(bufenv, "%s\t%02d:%02d\t%s", adresse, info_temps->tm_hour, info_temps->tm_min, bufrec);
        printf("Serveur a reçu et diffuse : %s\n", bufenv);
        sendto(sock, bufenv, strlen(bufenv), 0, (struct sockaddr *)&addr_envoi, sizeof(addr_envoi));
    }
    exit(0);
}