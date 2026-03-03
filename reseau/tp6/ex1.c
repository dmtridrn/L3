#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define SIZE_MESS 100

int main(){

    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET6;
    hints.ai_socktype = SOCK_STREAM;

    struct addrinfo *r, *p;
    if ((getaddrinfo("lulu", "7", &hints, &r)) != 0) exit(EXIT_FAILURE);
    
    p = r;
    int fdsock;
    while(p != NULL){
        if((fdsock = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) > 0){
            if(connect(fdsock, p->ai_addr, p->ai_addrlen) == 0){
                break;
            }
            close(fdsock);
        }
        p = p->ai_next;
    }
    freeaddrinfo(r);

    

    char bufsend[SIZE_MESS];
	memset(bufsend, 0, SIZE_MESS);
  
	
    int ecrit;
    int i = 0;
    while(i<10){
        sprintf(bufsend, "Hello%d\n",i);
        ecrit = send(fdsock, bufsend, strlen(bufsend), 0);
        if(ecrit <= 0){
            perror("erreur ecriture");
            exit(3);
        }
    
        if(ecrit < strlen(bufsend))
            printf("les %lu derniers octet du message sont perdus\n",  strlen(bufsend) - ecrit);

        char bufrecv[SIZE_MESS+1];
        memset(bufrecv, 0, SIZE_MESS+1);
    
        int recu = recv(fdsock, bufrecv, SIZE_MESS * sizeof(char), 0);
        if (recu < 0){
            perror("erreur lecture");
            close(fdsock);
            exit(4);
        }
        if (recu == 0){
            printf("serveur off\n");
            close(fdsock);
            exit(0);
        }
    
        //bufrecv[recu] = '\0';
        printf("%s\n", bufrecv);
        sleep(1);
        i++;
    }

	//*** fermeture de la socket ***
	close(fdsock);
}