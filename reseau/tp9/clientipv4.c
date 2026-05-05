#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <net/if.h>

void *ecoute(void *arg){
    int sock = *((int *)arg);
    char buf[1029+INET_ADDRSTRLEN];
    while(1){
        int n = recv(sock, buf, sizeof(buf), 0);
        buf[n] = '\0';
        fprintf(stderr, "REÇU DU SERVEUR : %s", buf); 
        fflush(stderr);
    }
}

int main(){
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    int opt = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in serv;
    memset(&serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(10201);
    serv.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(sock, (struct sockaddr *)&serv, sizeof(serv));

    struct ip_mreqn group;
    memset(&group, 0, sizeof(group));
    inet_pton(AF_INET, "225.1.2.3", &group.imr_multiaddr);
    group.imr_ifindex = if_nametoindex("lo0");
    setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &group, sizeof(group));

    pthread_t ecouteur;
    pthread_create(&ecouteur, NULL, ecoute, &sock);

    struct sockaddr_in addr_envoi;
    memset(&addr_envoi, 0, sizeof(addr_envoi));
    addr_envoi.sin_family = AF_INET;
    addr_envoi.sin_port = htons(12121);
    inet_pton(AF_INET, "127.0.0.1", &addr_envoi.sin_addr);
    char bufenv[1024];
    while(1){
        int r = read(0, bufenv, sizeof(bufenv));
        bufenv[r] = '\0';
        sendto(sock, bufenv, r, 0, (struct sockaddr *)&addr_envoi, sizeof(addr_envoi));
    }
}