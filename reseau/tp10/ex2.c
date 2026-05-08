#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <time.h>
#include <poll.h>
#include <fcntl.h>

#define PORT 8080
#define MAX_BUFFER 512

int main() {
    srand(time(NULL));
    // 1. Initialisation de la socket serveur en IPv6
    int sock_serv = socket(AF_INET6, SOCK_STREAM, 0);
    if (sock_serv == -1) {
        perror("Erreur socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in6 addr_serv;
    memset(&addr_serv, 0, sizeof(addr_serv));
    addr_serv.sin6_family = AF_INET6;
    addr_serv.sin6_port = htons(PORT);
    addr_serv.sin6_addr = in6addr_any;

    // Optionnel mais très recommandé pour éviter l'erreur "Address already in use" au redémarrage
    int opt = 1;
    setsockopt(sock_serv, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    if (bind(sock_serv, (struct sockaddr *)&addr_serv, sizeof(addr_serv)) == -1) {
        perror("Erreur bind");
        exit(EXIT_FAILURE);
    }

    if (listen(sock_serv, 10) == -1) {
        perror("Erreur listen");
        exit(EXIT_FAILURE);
    }
    int sock_client = accept(sock_serv, NULL, NULL);
    int flags = fcntl(sock_client, F_GETFL, 0);
    if (flags == -1) { perror("fcntl GET"); }
    if (fcntl(sock_client, F_SETFL, flags | O_NONBLOCK) == -1) {
        perror("fcntl SET");
    }
    int fac1, fac2;
    int score = 0 ;

    for(int i = 1; i<=5; i++){
        char msg[100];
        fac1 = (rand() % 20) + 1;
        fac2 = (rand() % 20) + 1;
        int resultat_attendu = fac1 * fac2;
        int len = snprintf(msg, sizeof(msg), "\nQuestion %d: Combien font %d x %d ?\n", i, fac1, fac2);
        send(sock_client, msg, len, 0);

        struct pollfd pfd;
        pfd.fd = sock_client;
        pfd.events = POLLIN;
        pfd.revents = 0;

        int temps = 10;
        while(temps > 0){
            int ret = poll(&pfd, 1, 1000);//on bloque pendant 1 seconde
            if(ret == 0){
                char cpt_msg[10];
                int n = snprintf(cpt_msg, sizeof(cpt_msg), "%d...\n", temps);
                send(sock_client, cpt_msg, n, 0);
                temps--;
            }
            else {
                if(pfd.revents & POLLIN){
                    char reponse[10];
                    memset(reponse, 0, 10);
                    int lus = recv(sock_client, reponse, 10, 0);
                    int guess = atoi(reponse);
                    if (guess == resultat_attendu) {
                        send(sock_client, "Gagné !\n", 8, 0);
                        score++;
                    } else {
                        send(sock_client, "Faux !\n", 7, 0);
                    }
                    break;
                }
            }
        }
    }
    char bilan[50];
    int n = snprintf(bilan, sizeof(bilan), "\nJeu terminé. Score : %d/5\n", score);
    send(sock_client, bilan, n, 0);
    close(sock_client);
}