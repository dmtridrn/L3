#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

int main(int argc, char **argv){
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock < 0){
        exit(1);
    }

    struct sockaddr_in adrsock;
    memset(&adrsock, 0, sizeof(adrsock));
    adrsock.sin_family = AF_INET;
    adrsock.sin_port = htons(2121);
    adrsock.sin_addr.s_addr = htonl(INADDR_ANY);

    int r = connect(sock, (struct sockaddr *) &adrsock, sizeof(adrsock));
	if(r == -1){
		perror("echec de la connexion");
		exit(2);
	}

    int fd = open(argv[1], O_RDONLY);
    off_t taille = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);

    char buffer[1024];

    snprintf(buffer, sizeof(buffer), "%ld\n", (long)taille);
    send(sock, buffer, strlen(buffer), 0);
    memset(buffer, 0, sizeof(buffer));
    int lus;
    while(taille > 0){
        lus = read(fd, buffer, sizeof(buffer));
        if(lus == 0) break;
        send(sock, buffer, lus, 0);
        taille -= lus;
    }
    
    close(sock);
    return 0;

}