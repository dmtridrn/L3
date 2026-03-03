#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define SIZE_MESS 100

union sockadresse
{
    struct sockaddr_in sadr4;
    struct sockaddr_in6 sadr6;
};

int main(int argc, char **argv){

    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET6;
    hints.ai_flags = AI_V4MAPPED | AI_ALL;
    hints.ai_socktype = SOCK_STREAM;

    struct addrinfo *r, *p;
    if ((getaddrinfo(argv[1], "2628", &hints, &r)) != 0)
        exit(EXIT_FAILURE);

    p = r;
    int sock;
    while (p != NULL){
        if((sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) > 0){
            int opt = 0;
            setsockopt(sock, IPPROTO_IPV6, IPV6_V6ONLY, &opt, sizeof(opt));
            if(connect(sock, p->ai_addr, p->ai_addrlen) == 0){
                break;
            }
            close(sock);
        }
        p = p->ai_next;
    }
    if (p == NULL) exit(1);
    
    union sockadresse adr;
    memset(&adr, 0, sizeof(adr));
    if (p->ai_family == AF_INET){
        memcpy(&(adr.sadr4), (struct sockaddr_in *)p->ai_addr, p->ai_addrlen);
    }
    else{
        memcpy(&(adr.sadr6), (struct sockaddr_in6 *)p->ai_addr, p->ai_addrlen);
    }
    freeaddrinfo(r);

    char recu[512];
    memset(recu, 0, 512);
    int n = recv(sock, recu, sizeof(recu)-1, 0);
    if (n > 0) {
        recu[n] = '\0'; // On ferme la chaîne proprement
    }
    if(strncmp("220 ", recu, 4) != 0){
        exit(1);
    }
    puts("OKOKOK");
}