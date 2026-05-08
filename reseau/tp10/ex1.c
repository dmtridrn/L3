#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>

#define PORT 8080
#define MAX_BUFFER 512

int main() {
    // 1. Initialisation de la socket serveur en IPv6
    int sock_serv = socket(AF_INET6, SOCK_STREAM, 0);
    if (sock_serv == -1) {
        perror("Erreur socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in6 addr_serv;
    memset(&addr_serv, 0, sizeof(addr_serv));
    addr_serv.sin6_family = AF_INET6;
    addr_serv.sin6_port = htons(PORT);
    addr_serv.sin6_addr = in6addr_any;

    // Optionnel mais très recommandé pour éviter l'erreur "Address already in use" au redémarrage
    int opt = 1;
    setsockopt(sock_serv, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    if (bind(sock_serv, (struct sockaddr *)&addr_serv, sizeof(addr_serv)) == -1) {
        perror("Erreur bind");
        exit(EXIT_FAILURE);
    }

    if (listen(sock_serv, 10) == -1) {
        perror("Erreur listen");
        exit(EXIT_FAILURE);
    }

    fd_set a_surveiller, activite;
    FD_ZERO(&a_surveiller);
    FD_SET(sock_serv, &a_surveiller);
    int max_fd = sock_serv;

    char buff[MAX_BUFFER];

    while(1){
        activite = a_surveiller;
        if (select(max_fd + 1, &activite, NULL, NULL, NULL) == -1) {
            perror("Erreur select");
            break;
        }
        for(int i = 0; i <= max_fd; i++){
            if(FD_ISSET(i, &activite)){
                if(i == sock_serv){
                    printf("Client connecté\n");
                    int sock_client = accept(sock_serv, NULL, NULL);
                    FD_SET(sock_client, &a_surveiller);
                    if(sock_client > max_fd){
                        max_fd = sock_client;
                    }
                }
                else{
                    memset(buff, 0, MAX_BUFFER);
                    int lus = recv(i, buff, MAX_BUFFER, 0);
                    if(lus <= 0){
                        printf("client deco\n");
                        close(i);
                        FD_CLR(i, &a_surveiller);
                    }
                    else{
                        printf("renvoi de %s\n", buff);
                        int total = 0;
                        while(total < lus){
                            int env = send(i, buff+total, lus-total, 0);
                            total += env;
                        }
                    }
                }
            }
        }
    }
    close(sock_serv);
    return 0;
}