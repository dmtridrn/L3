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
    char buf[1029+INET6_ADDRSTRLEN];
    while(1){
        int n = recv(sock, buf, sizeof(buf), 0);
        buf[n] = '\0';
        fprintf(stderr, "REÇU DU SERVEUR : %s", buf); 
        fflush(stderr);
    }
}

int main(){
    int sock = socket(AF_INET6, SOCK_DGRAM, 0);
    int opt = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in6 serv;
    memset(&serv, 0, sizeof(serv));
    serv.sin6_family = AF_INET6;
    serv.sin6_port = htons(10201);
    serv.sin6_addr = in6addr_any;
    bind(sock, (struct sockaddr *)&serv, sizeof(serv));

    struct ipv6_mreq grp;
    inet_pton(AF_INET6, "ff02::4:3:2:1", &grp.ipv6mr_multiaddr);
    grp.ipv6mr_interface = if_nametoindex("lo0");
    setsockopt(sock, IPPROTO_IPV6, IPV6_JOIN_GROUP, &grp, sizeof(grp));

    pthread_t ecouteur;
    pthread_create(&ecouteur, NULL, ecoute, &sock);

    struct sockaddr_in6 addr_envoi;
    memset(&addr_envoi, 0, sizeof(addr_envoi));
    addr_envoi.sin6_family = AF_INET6;
    addr_envoi.sin6_port = htons(12121);
    inet_pton(AF_INET6, "::1", &addr_envoi.sin6_addr);
    char bufenv[1024];
    while(1){
        int r = read(0, bufenv, sizeof(bufenv));
        bufenv[r] = '\0';
        sendto(sock, bufenv, r, 0, (struct sockaddr *)&addr_envoi, sizeof(addr_envoi));
    }
}

