#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <net/if.h>

int main(){
    //socket réception
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    int loop = 1;
    setsockopt(sock, IPPROTO_IP, IP_MULTICAST_LOOP, &loop, sizeof(loop));
    //adresse réception
    struct sockaddr_in serv;
    memset(&serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(12121);
    serv.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(sock, (struct sockaddr *)&serv, sizeof(serv));

    //adresse envoi
    struct sockaddr_in addr_envoi;
    memset(&addr_envoi, 0, sizeof(addr_envoi));
    addr_envoi.sin_family = AF_INET;
    addr_envoi.sin_port = htons(10201);
    inet_pton(AF_INET, "225.1.2.3", &addr_envoi.sin_addr);

    struct ip_mreqn group;
    memset(&group, 0, sizeof(group));
    group.imr_ifindex = if_nametoindex("lo0");
    setsockopt(sock, IPPROTO_IP, IP_MULTICAST_IF, &group, sizeof(group));


    while(1){
        struct sockaddr_in client;
        socklen_t longu = sizeof(client);
        char adresse[INET_ADDRSTRLEN];

        char bufrec[1024];
        int lu = recvfrom(sock, bufrec, sizeof(bufrec), 0, (struct sockaddr *)&client, &longu);
        bufrec[lu] = '\0';

        time_t maintenant;
        struct tm *info_temps;
        char chaine_heure[10];
        time(&maintenant);
        info_temps = localtime(&maintenant);

        inet_ntop(AF_INET, &(client.sin_addr), adresse, sizeof(adresse));
        int len = strlen(bufrec) + 5 + INET_ADDRSTRLEN;
        char bufenv[len];
        sprintf(bufenv, "%s\t%02d:%02d\t%s", adresse, info_temps->tm_hour, info_temps->tm_min, bufrec);
        printf("Serveur a reçu et diffuse : %s\n", bufenv);
        sendto(sock, bufenv, strlen(bufenv), 0, (struct sockaddr *)&addr_envoi, sizeof(addr_envoi));
    }
    exit(0);
}