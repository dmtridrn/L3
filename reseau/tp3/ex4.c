#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(){
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock < 0){
        exit(1);
    }

    struct sockaddr_in adrsock;
    memset(&adrsock, 0, sizeof(adrsock));
    adrsock.sin_family = AF_INET;
    adrsock.sin_port = htons(2121);
    adrsock.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sock, (struct sockaddr *)&adrsock, sizeof(adrsock)) == -1){
        exit(1);
    }

    if (listen(sock, 0) == -1){
        exit(1);
    }

    puts("en attente de connexion");

    struct sockaddr_in adrclient;
    socklen_t size = sizeof(adrclient);
    memset(&adrclient, 0, size);

    int sockclient = accept(sock, (struct sockaddr *)&adrclient, &size);
    if (sockclient == -1){
        exit(1);
    }

    char addr_buf[INET_ADDRSTRLEN];
    memset(addr_buf, 0, sizeof(addr_buf));

    if (inet_ntop(AF_INET, &(adrclient.sin_addr), addr_buf, sizeof(addr_buf)) == NULL){
        perror("erreur recuperation de l’adresse IPv4");
    }
    else{
        printf("client connecte : %s %d\n", addr_buf, ntohs(adrclient.sin_port));
    }

    send(sockclient, "DEBUT\n", 6, 0);

    char buffer[12];
    for (int i = 0; i < 12; i++){
        recv(sockclient, buffer + i, 1, 0);
        if (buffer[i] == '\n'){
            buffer[i] = '\0';
            break;
        }
    }
    int taille = atoi(buffer);
    char contenu[1024];
    int fd = open("data.txt", O_WRONLY| O_CREAT | O_TRUNC, 0644);

    while(taille > 0){
        int lus = recv(sockclient, contenu, sizeof(contenu), 0);
        write(fd, contenu, lus);
        taille -= lus;
    }
    close(fd);
    send(sockclient, "BIEN REÇU\n", strlen("BIEN REÇU\n"), 0);

    close(sockclient);
    close(sock);
}