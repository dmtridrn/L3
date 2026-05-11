#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

void rec_affich(int sock){
    uint32_t longueur;
    recv(sock, &longueur, 4, 0);
    longueur = ntohl(longueur);
    char buffer[4096];
    memset(buffer, 0, 4096);
    int total = 0;
    while(total < longueur){
        int lus = recv(sock, buffer, 4095, 0);
        buffer[lus] = 0;
        printf("%s", buffer);
        total+=lus;
    }
}