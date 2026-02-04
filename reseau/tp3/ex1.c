#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(){

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock < 0) { exit(1); }

    struct sockaddr_in adrsock;
    memset(&adrsock, 0, sizeof(adrsock));
    adrsock.sin_family = AF_INET;
    adrsock.sin_port = htons(1234);
    adrsock.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sock, (struct sockaddr*) &adrsock, sizeof(adrsock)) == -1){
        exit(1);
    }

    if(listen(sock, 0) == -1){
        exit(1);
    }

    puts("en attente de connexion");

    while(1){
        struct sockaddr_in adrclient;
        socklen_t size = sizeof(adrclient);
        memset(&adrclient, 0, size);

        int sockclient = accept(sock, (struct sockaddr*) &adrclient, &size);
        if(sockclient == -1) { exit(1); }

        char addr_buf[INET_ADDRSTRLEN];
        memset(addr_buf, 0, sizeof(addr_buf));

        if (inet_ntop(AF_INET, &(adrclient.sin_addr), addr_buf, sizeof(addr_buf)) == NULL){
            perror("erreur recuperation de l’adresse IPv4");
        }
        else {
            printf("client connecte : %s %d\n", addr_buf, ntohs(adrclient.sin_port));
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