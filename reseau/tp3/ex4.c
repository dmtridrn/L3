#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(){
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adrsock;
    memset(&adrsock, 0, sizeof(adrsock));
    adrsock.sin_family = AF_INET;
    adrsock.sin_port = htons(2112);
    adrsock.sin_addr.s_addr = htonl(INADDR_ANY);
    socklen_t size = sizeof(adrsock);

    bind(sock, (struct sockaddr *) &adrsock, sizeof(adrsock));
    listen(sock, 0);
    int sockclient = accept(sock, (struct sockaddr *) &adrsock, &size);

    send(sockclient, "DEBUT\n", 6, 0);
    char buffer[100];
    recv(sockclient, buffer, sizeof(buffer), 0);
    int taille = atoi(buffer);
    char contenu[1000];
    int fd = open("data.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    while(taille > 0){
        int lus = recv(sockclient, contenu, sizeof(contenu), 0);
        write(fd, contenu, lus);
        taille -= lus;
    }
    close(fd);
    send(sockclient, "BIEN METISSSSSSSSSE\n", strlen("BIEN METISSSSSSSSSE\n"), 0);
    close(sockclient);
    close(sock);
}