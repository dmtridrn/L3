#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <netdb.h>

int main(int argc, char **argv){
    int len = strlen(argv[2])+1;

    char req[2+len+strlen("octet")+1];
    ssize_t lenreq = sizeof(req);
    uint16_t opcode = htons(1);

    memcpy(req, &opcode, sizeof(opcode));
    memcpy(req+2, argv[2], len);
    char * mode = "octet";
    memcpy(req+2+len, mode, strlen("octet")+1);

    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;

    struct addrinfo *r, *p;
    if ((getaddrinfo(argv[1], "69", &hints, &r)) != 0) exit(EXIT_FAILURE);
    int sock;
    p = r;
    while( p != NULL ){
        if((sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) > 0){
            break;
        }
        p = p->ai_next;
    }

    int env = sendto(sock, req, lenreq, 0, p->ai_addr, p->ai_addrlen);

    int recu;
    uint16_t numbloc = 1;
    int i = 1;
    char buf[516];
    struct sockaddr_in dest;
    socklen_t lonngu = sizeof(dest);
    int fd = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, 0644);
    uint16_t oprep = htons(4);
    char rep[4];
    memcpy(rep, &oprep, 2);
    while((recu = recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr*)&dest, &lonngu))>1){
        lonngu = sizeof(dest);
        memcpy(&numbloc, buf+2, 2);
        if(ntohs(numbloc) != i){
            continue;
        }
        memcpy(rep+2, &numbloc, 2);
        sendto(sock, rep, sizeof(rep), 0, (struct sockaddr*)&dest, lonngu);
        write(fd, buf+4, recu-4);
        if(recu < 516){
            break;
        }
        i++;
    }
}