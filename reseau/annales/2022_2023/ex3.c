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
#include <poll.h>

int main(int argc, char **argv){
    //étape 1
    int sock1 = socket(AF_INET6, SOCK_DGRAM, 0);

    struct sockaddr_in6 adr;
    memset(&adr, 0, sizeof(adr));
    adr.sin6_family = AF_INET6;
    inet_pton(AF_INET6, "ff02::1", &adr.sin6_addr);
    adr.sin6_port = htons(4444);

    char hello[5] = "HELLO";
    sendto(sock1, hello, 5, 0, (struct sockaddr *)&adr, sizeof(adr));

    //étape 2
    char ipa2[INET6_ADDRSTRLEN];
    memset(ipa2, 0, INET6_ADDRSTRLEN);
    struct sockaddr_in6 a1;
    socklen_t len = sizeof(a1);
    recvfrom(sock1, ipa2, INET6_ADDRSTRLEN, 0, (struct sockaddr *)&a1, &len);
    sendto(sock1, argv[1], strlen(argv[1])+1, 0, (struct sockaddr *)&a1, sizeof(a1));

    //adresse pr recevoir le HELLO
    int sock4444 = socket(AF_INET6, SOCK_DGRAM, 0);
    struct sockaddr_in6 adr2 = {AF_INET6, htons(4444), 0, IN6ADDR_ANY_INIT, 0};
    int ok = 1;
    setsockopt(sock4444, SOL_SOCKET, SO_REUSEPORT, &ok, sizeof(ok));
    bind(sock4444, (struct sockaddr *)&adr2, sizeof(adr2));
    struct ipv6_mreq mreq;
    inet_pton(AF_INET6, "ff12::ae2:b", &mreq.ipv6mr_multiaddr);
    mreq.ipv6mr_interface = 0;
    opt(sock4444, IPPROTO_IPV6, IPV6_JOIN_GROUP, &mreq, sizeof(mreq));

    //pour écouter le pair précédent
    int sock5555 = socket(AF_INET6, SOCK_DGRAM, 0);
    struct sockaddr_in6 adr3 = {AF_INET6, htons(5555), 0, IN6ADDR_ANY_INIT, 0};
    socklen_t len5555 = sizeof(adr3);
    setsockopt(sock5555, SOL_SOCKET, SO_REUSEPORT, &ok, sizeof(ok));
    bind(sock5555, (struct sockaddr *)&adr3, sizeof(adr3));

    struct pollfd fds[3];
    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;
    fds[1].fd = sock4444;
    fds[1].events = POLLIN;
    fds[2].fd = sock5555;
    fds[2].events = POLLIN;
    int timeout = -1;
    while(1){
        int ret = poll(fds, 3, 5000);
        if(fds[0].revents & POLLIN){
            char buff[255];
            int total = 0;
            int lu;
            while((lu = read(stdin, buff+total, 64))){
                total+=lu;
            }
            //r2
        }
        if(fds[1].revents & POLLIN){
            char buffrec[5];
            char ex[5] = "HELLO";
            recvfrom(sock4444, buffrec, 5, 0, (struct sockaddr *)&adr3, &len5555);
            if(memcmp(ex, buffrec, 5) == 0){
                //r3
            }
        }
        if(fds[2].revents & POLLIN){
            char buff[255];
            int total = 0;
            int lu;
            while((lu = read(stdin, buff+total, 64))){
                total+=lu;
            }
            //r1
            struct pollfd fd1;
            fd1.events = POLLIN;
            fd1.fd = STDIN_FILENO;
            printf("%s\n", buff);
            while(1){
                int ret = poll(&fd1, 1, 20000);
                if(ret == 0){//personne a dit qu'il sen occupe on envoie au suivant
                    struct sockaddr_in6 adra2;
                    memset(&adra2, 0, sizeof(adra2));
                    adra2.sin6_family = AF_INET6;
                    inet_pton(AF_INET6, ipa2, &adra2.sin6_addr);
                    adra2.sin6_port = htons(5555);
                    sendto(sock1, buff, strlen(buff), 0, (struct sockaddr *)&adra2, sizeof(adra2));
                    break;
                }
                if(fd1.revents & POLLIN){
                    break;
                }
            }
        }
    }
}