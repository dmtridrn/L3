#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>

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

    uint16_t *qtype;
    *qtype = htons(1); 
    qinfo += sizeof(uint16_t);

    uint16_t *qclass;
    *qclass = htons(1); 
    qinfo += sizeof(uint16_t);

    int packet_size = qinfo - buffer;

    if (sendto(sock, buffer, packet_size, 0, (struct sockaddr*)&dest, sizeof(dest)) < 0) {
        perror("Erreur lors de l'envoi");
        return 1;
    }

    return 0;
}