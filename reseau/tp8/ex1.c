#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

struct entete{
    uint16_t id;
    uint16_t flags;
    uint16_t qdcount;
    uint16_t ancount;
    uint16_t nscount;
    uint16_t arcount;
}typedef entete;

void constr_entete(entete *e){
    e->id = htons(1);
    e->flags = htons(0x0100);
    e->qdcount = htons(1);
    e->ancount = 0;
    e->nscount = 0;
    e->arcount = 0;
}

void constr_qname(unsigned char *qname, char *hostname) {
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

int main(int argc, char **argv){
    entete e;
    memset(&e,0,sizeof(e));
    constr_entete(&e);
    uint8_t buf[strlen(argv[1])+2];
    constr_qname(buf, argv[1]);
    char envoi[sizeof(e) + sizeof(buf) + 4];
    memcpy(envoi, &e, sizeof(e));
    memcpy(envoi + sizeof(e), buf, sizeof(buf));
    uint16_t qtype = htons(1);
    uint16_t qclass = htons(1);
    memcpy(envoi + sizeof(e) + sizeof(buf), &qtype, 2);
    memcpy(envoi + sizeof(e) + sizeof(buf) + 2, &qclass, 2);

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in serv;
    memset(&serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(53);

    if (inet_aton("192.168.1.254", &serv.sin_addr) == 0) {
        perror("IP invalide");
        exit(1);
    }
    uint8_t buffer[512];
    sendto(sock, envoi, sizeof(envoi), 0, (struct sockaddr*)&serv, sizeof(serv));
    int taillerep = recvfrom(sock, buffer, sizeof(buffer), 0, NULL, NULL);
    if((buffer[3] & 15)){
        perror("erreur");
        exit(0);
    }
    uint16_t ancount;
    memcpy(&ancount, buffer+6, 2);
    ancount = ntohs(ancount);
    uint16_t curs = sizeof(entete);
    while(1){
        if(buffer[curs] == 0){
            curs++;
            break;
        }
        else if(buffer[curs] >= 192){
            curs += 2;
            break;
        }
        else{
            curs += (buffer[curs]+1);
        }
    }
    for(int i = 0; i<ancount; i++){
        while(1){
            if(buffer[curs] == 0){
                curs++;
                break;
            }
            else if(buffer[curs] >= 192){
                curs += 2;
                break;
            }
            else{
                curs += (buffer[curs]+1);
            }
        }
        uint16_t type;
        memcpy(&type, buffer+curs, 2);
        curs += 8;
        if(ntohs(type) == 1){
            char addr_buf[INET_ADDRSTRLEN];
            memset(addr_buf, 0, sizeof(addr_buf));
            inet_ntop(AF_INET, &buffer[curs], addr_buf, sizeof(addr_buf));
            printf("%s\n", addr_buf);
        }
        else if(ntohs(type) == 1){
            char addr_buf[INET6_ADDRSTRLEN];
            memset(addr_buf, 0, sizeof(addr_buf));
            inet_ntop(AF_INET6, &buffer[curs], addr_buf, sizeof(addr_buf));
            printf("%s\n", addr_buf);
        }
    }
    exit(0);
}