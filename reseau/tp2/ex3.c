#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ADR "192.168.70.95"
#define SIZE_MESS 100

int main(){

    int fdsock = socket(PF_INET, SOCK_STREAM, 0);
	if(fdsock == -1){
		perror("creation socket");
		exit(1);
	}

    struct sockaddr_in address_sock;
	memset(&address_sock, 0,sizeof(address_sock));
	address_sock.sin_family = AF_INET;
	address_sock.sin_port = htons(37);
	inet_pton(AF_INET, ADR, &address_sock.sin_addr);

    int r = connect(fdsock, (struct sockaddr *) &address_sock, sizeof(address_sock));
	if(r == -1){
		perror("echec de la connexion");
		exit(2);
	}

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

	//*** fermeture de la socket ***
	close(fdsock);
}