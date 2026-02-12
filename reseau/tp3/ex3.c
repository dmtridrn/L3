#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

int main(){
    srandom(time(NULL));
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

    char buffer[65535];
    int tentatives = 0;
    int reponse = random() % 65535;
    printf("%d\n", reponse);
    
    int fin;
    while(tentatives < 21){
        ssize_t tailleguess = recv(sockclient, buffer, sizeof(buffer), 0);
        char buf[65535];
        strncpy(buf, buffer, tailleguess);
        int guess = atoi(buf);
        memset(buf, 0, sizeof(buf));
        if(guess < reponse){
            snprintf(buf, sizeof(buf), "PLUS ! %d tentavies restantes\n", 21-tentatives);
            send(sockclient, buf, strlen(buf), 0);
        }
        else if(guess > reponse){
            snprintf(buf, sizeof(buf), "MOINS ! %d tentavies restantes\n", 21-tentatives);
            send(sockclient, buf, strlen(buf), 0);
        }
        else if(guess == reponse){
            snprintf(buf, sizeof(buf), "GAGNE\n");
            send(sockclient, buf, strlen(buf), 0);
            break;
        }
        tentatives++;
    }

    if (tentatives >= 21){
        char buf[256];
        snprintf(buf, sizeof(buf), "PERDU ! Le nombre etait %d\n", reponse);
        send(sockclient, buf, strlen(buf), 0);
    }


    close(sockclient);
    close(sock);
}