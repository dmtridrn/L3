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

int main(int argc, char **argv){

    char *filename = argv[2];
    char *mode = "octet";
    int packet_size = 2 + strlen(filename) + 1 + strlen(mode) + 1;
    char paquet[512];
    memset(paquet, 0, 512);
    int offset = 0;
    paquet[offset++] = 0;
    paquet[offset++] = 1;
    memcpy(paquet + offset, filename, strlen(filename));
    offset += strlen(filename);
    paquet[offset++] = 0; 
    memcpy(paquet + offset, mode, strlen(mode));
    offset += strlen(mode);
    paquet[offset++] = 0;
    
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;

    struct addrinfo *p;
    if ((getaddrinfo(argv[1], "69", &hints, &p)) != 0) exit(EXIT_FAILURE);
    int fdsock = socket(p->ai_family, p->ai_socktype, 0);
    ssize_t sent = sendto(fdsock, paquet, packet_size, 0, p->ai_addr, p->ai_addrlen);
    freeaddrinfo(p);

}