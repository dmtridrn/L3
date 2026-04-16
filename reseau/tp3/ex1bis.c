#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(){
    int sock = socket(PF_INET6, SOCK_STREAM, 0);
    struct sockaddr_in6 adrsock;
    memset(&adrsock, 0, sizeof(adrsock));
    adrsock.sin6_family = AF_INET6;
    adrsock.sin6_port = htons(2121);
    adrsock.sin6_addr = in6addr_any;
    socklen_t size = sizeof(struct sockaddr);

    bind(sock, (struct sockaddr*) &adrsock, sizeof(adrsock));
    listen(sock, 0);

    while(1){
        int sockclient = accept(sock, (struct sockaddr*) &adrsock, &size);

        //affichage
        char addr_buf[INET_ADDRSTRLEN];
        memset(addr_buf, 0, sizeof(addr_buf));
        if (inet_ntop(AF_INET6, &(adrsock.sin6_addr), addr_buf, sizeof(addr_buf)) == NULL)
        perror("erreur recuperation de l’adresse IPv4");
        else
        printf("client connecte : %s %d\n", addr_buf, ntohs(adrsock.sin6_port));

        char buffer[1000];
        int lus;
        while((lus = recv(sockclient, buffer, 1000, 0)) > 0){
            send(sockclient, buffer, lus, 0);
        }
        close(sockclient);
    }
    close(sock);
}