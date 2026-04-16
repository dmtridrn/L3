#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(){
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adrsock;
    memset(&adrsock, 0, sizeof(adrsock));
    adrsock.sin_family = AF_INET;
    adrsock.sin_port = htons(2121);
    adrsock.sin_addr.s_addr = htonl(INADDR_ANY);
    socklen_t size = sizeof(struct sockaddr);

    bind(sock, (struct sockaddr*) &adrsock, sizeof(adrsock));
    listen(sock, 0);
    int sockclient = accept(sock, (struct sockaddr*) &adrsock, &size);

    //affichage
    char addr_buf[INET_ADDRSTRLEN];
    memset(addr_buf, 0, sizeof(addr_buf));
    if (inet_ntop(AF_INET, &(adrsock.sin_addr), addr_buf, sizeof(addr_buf)) == NULL)
    perror("erreur recuperation de l’adresse IPv4");
    else
    printf("client connecte : %s %d\n", addr_buf, ntohs(adrsock.sin_port));

    char buffer[1000];
    int lus;
    while((lus = recv(sockclient, buffer, 1000, 0)) > 0){
        send(sockclient, buffer, lus, 0);
    }
    close(sockclient);
    close(sock);
}