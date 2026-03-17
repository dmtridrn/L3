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

typedef struct{
    char buff[2*SIZE_MESS + 1];
    int cur;
    int size;
} buf_t;

int find_newline(buf_t *buf){
    buf->buff[buf->size] = '\0';
    char *ptr = strstr(buf->buff, "\r\n");
    if(ptr == NULL){
        return -1;
    }
    int index = (int)(ptr - buf->buff);
    return index;
}

int is_last_line(buf_t *buf){
    if (strncmp(buf->buff, "250", 3) == 0 || strncmp(buf->buff, "552", 3) == 0) {
        return 1;
    }
    return 0;
}


int main(int argc, char **argv){
    buf_t buffer;
    memset(0, &buffer, sizeof(buf_t));
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
    if (p == NULL){
        perror("NAN pas connect");
        exit(1);
    }
    
    union sockadresse adr;
    memset(&adr, 0, sizeof(adr));
    if (p->ai_family == AF_INET){
        memcpy(&(adr.sadr4), (struct sockaddr_in *)p->ai_addr, p->ai_addrlen);
    }
    else{
        memcpy(&(adr.sadr6), (struct sockaddr_in6 *)p->ai_addr, p->ai_addrlen);
    }
    freeaddrinfo(r);

    int n = recv(sock, buffer.buff, sizeof(buffer.buff)-1, 0);
    if (n > 0) {
        buffer.buff[n] = '\0'; // On ferme la chaîne proprement
    }
    if(strncmp("220 ", buffer.buff, 4) != 0){
        perror("NAN pas 220");
        exit(1);
    }
    puts("OKOKOK");

    char ecr[100];
    memset(&ecr, 0, 100);
    snprintf(ecr, sizeof(ecr)-1, "DEFINE * %s\r\n", argv[2]);
    send(sock, ecr, strlen(ecr), 0);
    memset(&buffer.buff, 0, sizeof(buffer.buff));
    char check[4];

    while(1){
        n = recv(sock, buffer.buff, sizeof(buffer.buff)-1, 0);
        buffer.size += n;
        if(n <= 0){
            exit(1);
        }
        buffer.buff[n] = '\0';
        printf("%s", buffer.buff);
        if(strstr(buffer.buff, "\r\n.\r\n") != NULL){
            break;

        }
    }
    exit(0);
}