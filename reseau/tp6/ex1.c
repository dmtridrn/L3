#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>

#define SIZE_MESS 100

int main(){

    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET6;
    hints.ai_socktype = SOCK_STREAM;

    struct addrinfo *r, *p;
    if ((getaddrinfo("lulu", "7", &hints, &r)) != 0) exit(EXIT_FAILURE);
    int sock;

    p = r;
    while( p != NULL ){
        if((sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) > 0){
            if(connect(sock, p->ai_addr, p->ai_addrlen) == 0){
                break;
            }
            close(sock);
        }
        p = p->ai_next;
    }

    if( p == NULL) exit(EXIT_FAILURE);

    if(r){
        freeaddrinfo(r);
    }

    //ici sensé etre connecté

    char bufsend[SIZE_MESS];
	memset(bufsend, 0, SIZE_MESS);


    int ecrit;
    int i = 0;
    while(i<10){
        sprintf(bufsend, "Métisse %d\n",i);
        ecrit = send(sock, bufsend, strlen(bufsend), 0);
        if(ecrit <= 0){
            perror("erreur ecriture");
            exit(3);
        }

        if(ecrit < strlen(bufsend))
            printf("les %lu derniers octet du message sont perdus\n",  strlen(bufsend) - ecrit);

        char bufrecv[SIZE_MESS+1];
        memset(bufrecv, 0, SIZE_MESS+1);
    
        int recu = recv(sock, bufrecv, SIZE_MESS * sizeof(char), 0);
        if (recu < 0){
            perror("erreur lecture");
            close(sock);
            exit(4);
        }
        if (recu == 0){
            printf("serveur off\n");
            close(sock);
            exit(0);
        }
    
        //bufrecv[recu] = '\0';
        printf("%s\n", bufrecv);
        sleep(1);
        i++;
    }

	//*** fermeture de la socket ***
	close(sock);
}