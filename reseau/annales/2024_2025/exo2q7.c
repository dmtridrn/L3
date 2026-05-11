#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <poll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

void prepa_socket(int sock, const char *IP, int port);
struct sockaddr_in6 prepa_adr(const char *IP, int port);

int main(){
    int sock_env = socket(AF_INET6, SOCK_DGRAM, 0);
    int sock_rec = socket(AF_INET6, SOCK_DGRAM, 0);
    char buff[1024];
    int timeout = -1;

    struct pollfd fds[2];
    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;
    fds[1].fd = sock_rec;
    fds[1].events = POLLIN;

    prepa_socket(sock_rec, "ff12::c56:8a61:3cd5:45b1", 4322);//rejoins le groupe aussi
    struct sockaddr_in6 adr_dest = prepa_adr("ff12::55ba:cf94:f048:ab83", 2525);

    while(1){
        int ret = poll(fds, 2, timeout);
        if(ret == 0){
            break;
        }
        if(fds[0].revents & POLLIN){
            fgets(buff, 1024, stdin);
            if(strcmp(buff, "/safexit\n") == 0){
                timeout = 1000;
            }
            else{
                sendto(sock_env, buff, strlen(buff), 0, (struct sockaddr *)&adr_dest, sizeof(adr_dest));
            }
        }
        if(fds[1].revents & POLLIN){
            int n = recv(sock_rec, buff, sizeof(buff) - 1, 0);
            buff[n] = '\0';
            printf("Reçu : %s", buff);
        }
    }
    close(sock_env);
    close(sock_rec);
    exit(0);
}