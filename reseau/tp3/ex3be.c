#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

int main(){
    srandom(time(NULL));
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

    //affichage blc
    char addr_buf[INET_ADDRSTRLEN];
    memset(addr_buf, 0, sizeof(addr_buf));
    if (inet_ntop(AF_INET, &(adrsock.sin_addr), addr_buf, sizeof(addr_buf)) == NULL)
    perror("erreur recuperation de l’adresse IPv4");
    else
    printf("client connecte : %s %d\n", addr_buf, ntohs(adrsock.sin_port));

    int reponse = random() % 65535;
    printf("%d\n", reponse);
    uint16_t rep;
    int tentatives_restantes = 20;
    uint8_t envoi[2]; //premier octet: nombre d'essais deuxieme: 0 ou 1
    while(tentatives_restantes > 0){
        envoi[1] = tentatives_restantes;
        recv(sockclient, &rep, 2, 0);
        uint16_t vraierep = ntohs(rep);
        if(vraierep > reponse){
            envoi[1] = 0;
            send(sockclient, envoi, 2, 0);
        }
        else if(vraierep < reponse){
            envoi[1] = 1;
            send(sockclient, envoi, 2, 0);
        }
        else if(vraierep == reponse){
            envoi[1] = 1;
            send(sockclient, envoi, 2, 0);
            break;
        }
        tentatives_restantes --;
    }
    if(tentatives_restantes == 0){
        envoi[1] = 0;
        send(sockclient, envoi, 2, 0);
    }
    close(sockclient);
    close(sock);
}