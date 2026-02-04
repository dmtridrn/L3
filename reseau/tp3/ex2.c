#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(){

    int sock = socket(PF_INET6, SOCK_STREAM, 0);
    if(sock < 0) { exit(1); }

    struct sockaddr_in6 adrsock;
    memset(&adrsock, 0, sizeof(adrsock));
    adrsock.sin6_family = AF_INET6;
    adrsock.sin6_port = htons(1234);
    adrsock.sin6_addr = in6addr_any;

    if(bind(sock, (struct sockaddr*) &adrsock, sizeof(adrsock)) == -1){
        exit(1);
    }

    if(listen(sock, 0) == -1){
        exit(1);
    }

    puts("en attente de connexion");

    while(1){
        struct sockaddr_in6 adrclient;
        socklen_t size = sizeof(adrclient);
        memset(&adrclient, 0, size);

        int sockclient = accept(sock, (struct sockaddr*) &adrclient, &size);
        if(sockclient == -1) { exit(1); }

        char addr_buf[INET6_ADDRSTRLEN];
        memset(addr_buf, 0, sizeof(addr_buf));

        if (inet_ntop(AF_INET6, &(adrclient.sin6_addr), addr_buf, sizeof(addr_buf)) == NULL){
            perror("erreur recuperation de l'adresse IPv6");
        }
        else {
            printf("client connecte : %s %d\n", addr_buf, ntohs(adrclient.sin6_port));
        }

        char buffer[1024];
        int lus;
        while((lus = recv(sockclient, buffer, 1023, 0)) > 0){
            printf("message reçu\n");
            send(sockclient, buffer, lus, 0);
        }
        close(sockclient);
    }

    close(sock);
}