#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

int main(){
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

    int min = 0;
    int max = 65535;
    char buffer[256];

    for (int i = 0; i < 20; i++) {
        // Algorithme de recherche dichotomique
        int guess = min + (max - min) / 2;
        printf("Tentative %d : Je propose %d\n", i + 1, guess);

        // Conversion du nombre en string pour l'envoi
        char msg[32];
        int len = snprintf(msg, sizeof(msg), "%d", guess);
        send(sock, msg, len, 0);

        // Réception de la réponse du serveur
        memset(buffer, 0, sizeof(buffer));
        ssize_t n = recv(sock, buffer, sizeof(buffer) - 1, 0);
        if (n <= 0) break;

        printf("Serveur dit : %s", buffer);

        // Analyse de la réponse
        if (strstr(buffer, "PLUS")) {
            min = guess + 1;
        } else if (strstr(buffer, "MOINS")) {
            max = guess - 1;
        } else if (strstr(buffer, "GAGNE") || strstr(buffer, "PERDU")) {
            break;
        }
    }

    close(sock);
    return 0;

}