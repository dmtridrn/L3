#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUF_SIZE 1024

int main(int argc, char const *args[]) {
    int sock1 = socket(AF_INET6, SOCK_DGRAM, 0);

    struct sockaddr_in6 adr;
    memset(&adr, 0, sizeof(adr));
    adr.sin6_family = AF_INET6;
    inet_pton(AF_INET6, "ff12::ae2:b", &adr.sin6_addr);
    adr.sin6_port = htons(1212);

    char buf[BUF_SIZE];
    int l;
    l = sprintf(buf, "%s\0%s\0", "nivose.informatique.univ-paris-diderot.fr", args[1]);
    sendto(sock1, buf, l, 0, (struct sockaddr*)&adr, sizeof(adr));
    close(sock1);

    int sock2 = socket(PF_INET6, SOCK_STREAM, 0);
    struct sockaddr_in6 adr2 = {AF_INET6, htons(atoi(args[1])), 0, IN6ADDR_ANY_INIT, 0};
    bind(sock2, (struct sockaddr *) &adr2, sizeof(adr2));
    listen(sock2, 0);

    int sock3 = accept(sock2, NULL, NULL);
    int total = 0;
    while(total < 8){
        int lu = recv(sock3, buf+total, 8, 0);
        total += lu;
    }
    buf[total-1] = 0;
    printf("%s\n", buf);
    int result;
    scanf("%d", &result);
    result = htonl(result);
    send(sock3, &result, sizeof(result), 0);
    close(sock2);    close(sock3);
    return 0;
}