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
#include <time.h>

int main() {
    int sock=socket(PF_INET, SOCK_DGRAM, 0);

    int ok=1;
    setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &ok, sizeof(ok));

    struct sockaddr_in adr;
    memset(&adr, 0, sizeof(adr));
    adr.sin_family = AF_INET;
    adr.sin_port = htons(1234);
    inet_pton(AF_INET, "255.255.255.255", &adr.sin_addr);

    int i, nb;
    srand(time(NULL));
    for(i=0; i<=20; i++) {
        nb = htonl(rand()%50-25);
        sendto(sock, &nb, sizeof(nb), 0, (struct sockaddr*) &adr, sizeof(struct sockaddr_in));
    }

    close(sock);
    return 0;
}