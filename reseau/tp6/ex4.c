#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>

int main(int argc, char **argv){
    
    struct sockaddr_in6 sockfd;

    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET6;
    hints.ai_flags = AI_V4MAPPED | AI_ALL;
    hints.ai_socktype = SOCK_STREAM;

    struct addrinfo *r, *p;
    if ((getaddrinfo(argv[1], "2628", &hints, &r)) != 0){
        exit(EXIT_FAILURE);
    } 

    p = r;
    int sock;
    while( p != NULL ){
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

    //affichage facultatif mais bon a savoir si besoin de stocker l'addresse 
    memcpy(&(sockfd), (struct sockaddr_in6 *)p->ai_addr, p->ai_addrlen);
    char addr_buf[INET6_ADDRSTRLEN];
    memset(addr_buf, 0, sizeof(addr_buf));
    if (inet_ntop(AF_INET6, &(sockfd.sin6_addr), addr_buf, sizeof(addr_buf)) == NULL)
    perror("erreur recuperation de l’adresse IPv4");
    else
    printf("client connecte : %s %d\n", addr_buf, ntohs(sockfd.sin6_port));

    freeaddrinfo(r);
    
    char bufconfirm[5];
    memset(&bufconfirm, 0, 4);
    int l = recv(sock, bufconfirm, sizeof(bufconfirm)-1, 0);
    bufconfirm[l] = '\0';
    if(strcmp("220 ", bufconfirm) != 0){
        printf("non métisse \n");
        exit(1);
    }
    puts("OUI métisse");

    char buf[512];
    char ecr[100];
    memset(&ecr, 0, sizeof(ecr));
    snprintf(ecr, sizeof(ecr), "DEFINE * %s\r\n", argv[2]);
    send(sock, ecr, strlen(ecr), 0);
    memset(&buf, 0, sizeof(buf));
    int n;
    while(1){
        n = recv(sock, buf, sizeof(buf)-1, 0);
        buf[n] = '\0';
        printf("%s", buf);
        if(strstr(buf, "\r\n.\r\n") != NULL){
            break;
        }
    }
    exit(0);
}