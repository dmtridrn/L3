#include <errno.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdint.h>

int main(){
    int sock = socket(AF_INET6, SOCK_DGRAM, 0);
    struct sockaddr_in6 servadr;
    memset(&servadr, 0, sizeof(servadr));
    servadr.sin6_family = AF_INET6;
    servadr.sin6_addr = in6addr_any;
    servadr.sin6_port = htons(7777);

    struct sockaddr_in6 adr_client;
    socklen_t len = sizeof(adr_client);

    char buf[1024];
    int lu = recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr *)&adr_client, &len);
    buf[lu] = '\0';
    if(!fic_exist(buf)){
        sendto(sock, "NOK", 3, 0, (struct sockaddr *)&adr_client, len);
        exit(0);
    }
    int taille = fic_taille(buf);
    uint16_t taille_max = htons(1024);
    uint32_t nb = htonl(taille / 1024);
    char header[8];
    header[0] = 'O';
    header[1] = 'K';
    memcpy(header + 2, &taille_max, sizeof(taille_max));
    memcpy(header + 4, &nb, sizeof(nb));
    sendto(sock, header, sizeof(header), 0, (struct sockaddr *)&adr_client, len);
    char a_envoyer[taille_max];
    struct pollfd fds[1];

    fds[0].fd = sock;
    fds[0].events = POLLIN;
    for(int i = 0; i<nb; i++){
        int lus= lire_fic(buf, a_envoyer, i, taille_max);
        mess_num(i,a_envoyer);
        sendto(sock, buf, lus, 0, (struct sockaddr *)&adr_client, len);
    }
    while(1){
        int ev = poll(fds, 1, 5000);
        if(ev > 0){
            if (fds[0].revents & POLLIN) {
                
            }
        }
    }
}
