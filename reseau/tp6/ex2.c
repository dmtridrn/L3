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

union sockadresse {
    struct sockaddr_in sadr4;
    struct sockaddr_in6 sadr6;
};

int main(int argc, char **argv){

    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    struct addrinfo *r, *p;
    if ((getaddrinfo(argv[1], NULL, &hints, &r)) != 0) exit(EXIT_FAILURE);
    
    p = r;
    while(p != NULL){
        char ip_str[INET6_ADDRSTRLEN];
        union sockadresse adr;
        memset(&adr, 0, sizeof(adr));
        if(p->ai_family == AF_INET){
            memcpy(&(adr.sadr4), (struct sockaddr_in *) p->ai_addr, p->ai_addrlen);
            inet_ntop(AF_INET, &(adr.sadr4.sin_addr), ip_str, sizeof(ip_str));
        }
        else{
            memcpy(&(adr.sadr6), (struct sockaddr_in6 *) p->ai_addr, p->ai_addrlen);
            inet_ntop(AF_INET6, &(adr.sadr6.sin6_addr), ip_str, sizeof(ip_str));
        }
        char buffer[SIZE_MESS];
        snprintf(buffer, sizeof(buffer), "Adresse trouvée: %s\n", ip_str);
        printf("%s", buffer);
        p = p->ai_next;
    }
    freeaddrinfo(r);
}