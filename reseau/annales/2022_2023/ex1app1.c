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

int main(){
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    struct addrinfo *r, *p;
    getaddrinfo("hope", "4444", &hints, &r);
    int sock;
    p = r;
    while( p != NULL ){
        sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if(connect(sock, p->ai_addr, p->ai_addrlen) == 0){
            break;
        }
        close(sock);
    }
    p = p->ai_next;
    if(r){
        freeaddrinfo(r);
    }
}