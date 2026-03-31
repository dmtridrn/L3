#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

struct entete {
    uint16_t id;      
    uint16_t flags;   
    uint16_t qdcount; 
    uint16_t ancount; 
    uint16_t nscount; 
    uint16_t arcount; 
};

void build_entete(struct entete *h) {
    h->id = htons(0x1234);
    h->flags = htons(0x0100);
    h->qdcount = htons(1);    
    h->ancount = 0;
    h->nscount = 0;
    h->arcount = 0;
}

void build_qname(unsigned char *qname, char *hostname) {
    int cur = 0;
    strcat(hostname, ".");
    for (int i = 0; i < strlen(hostname); i++) {
        if (hostname[i] == '.') {
            *qname++ = i - cur;
            for (; cur < i; cur++) {
                *qname++ = hostname[cur];
            }
            cur++;
        }
    }
    *qname = 0;
}

int main(int argc, char *argv[]) {
    char *hostname = argv[1]; 
    
    char *dns_ip = (argc > 2) ? argv[2] : "8.8.8.8"; 

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("Erreur création socket");
        return 1;
    }

    struct sockaddr_in dest;
    dest.sin_family = AF_INET;
    dest.sin_port = htons(53);
    dest.sin_addr.s_addr = inet_addr(dns_ip);

    unsigned char buffer[512]; 
    memset(buffer, 0, 512);
    
    struct entete *dns_header = (struct entete *)buffer;
    build_entete(dns_header);

    unsigned char *qname = buffer + sizeof(struct entete);

    char host_copy[256];
    strncpy(host_copy, hostname, 255);
    host_copy[255] = '\0';
    
    build_qname(qname, host_copy);

    unsigned char *qinfo = qname + strlen(hostname) + 2;

    uint16_t type = htons(1);
        uint16_t class = htons(1);

        memcpy(qinfo, &type, 2);
        qinfo += 2;
        memcpy(qinfo, &class, 2);
        qinfo += 2;

    int packet_size = qinfo - buffer;

    if (sendto(sock, buffer, packet_size, 0, (struct sockaddr*)&dest, sizeof(dest)) < 0) {
        perror("Erreur lors de l'envoi");
        return 1;
    }
    socklen_t addrlen = sizeof(dest);
    if (recvfrom(sock, buffer, 512, 0, (struct sockaddr*)&dest, &addrlen) < 0) {
        perror("Erreur lors de l'envoi");
        return 1;
    }
    struct entete *reponse = (struct entete*)buffer;
    uint16_t flags = ntohs(reponse->flags);
    int rcode = flags & 0x000F; 
    if (rcode != 0) {
        printf("err dns: %d\n", rcode); 
        return 1;
    }

    unsigned char *curs = buffer + packet_size + 10;
    uint16_t rdlength;
    memcpy(&rdlength, curs, 2);
    rdlength = ntohs(rdlength);
    curs += 2;

    if (rdlength == 4) {
        printf("Adresse IP : %d.%d.%d.%d\n", curs[0], curs[1], curs[2], curs[3]);
    }

    close(sock);
    return 0;
}