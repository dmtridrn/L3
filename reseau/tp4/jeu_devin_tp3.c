#include <arpa/inet.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFSIZE 100

int server_1p();


int main(int argn,char** args) {
  if(argn<=1|| strcmp(args[1],"-1p")==0){
    server_1p();
  }
}

/***************LES FONCTIONS DE LECTURE ET ECRITURE SUR SOCKET ******************/

int lire_nb(int sock, char *buf) {
	int taille, ind = 0;
	do {
		if((taille = recv(sock, buf+ind, BUFSIZE-1-ind, 0)) < 0) {
			perror("recv");
			exit(1);
		}
		ind += taille;
	} while(ind < BUFSIZE-1 && taille != 0 && !memchr(buf, '\n', ind));
	
	if(ind > BUFSIZE){
		fprintf(stderr, "erreur format message recu\n");
		exit(1);
	}
	buf[ind] = 0;

	return ind;
}

int ecrire_nb(int sock, char *buf) {
	int lg = 0, lu;
	do {
		if((lu = send(sock, buf, strlen(buf), 0)) <= 0) {
			perror("send");
			exit(1);
		}
		lg += lu;
	} while(lg < strlen(buf));

	return lg;
}

/***************LES FONCTIONS DE JEU ******************/	

/**
 * fait tourner une partie pour un joueur dont le socket est passé en argument
 */
void game_1p(int sock) {
  srandom(time(NULL) + sock);
  
  unsigned short int n = random() % (1 << 16); 
  printf("nb mystere pour partie socket %d = %d\n", sock, n);

  unsigned short int guess;
  int taille = 0;
  int tentatives = 20;
  int gagne = 0;
  char buff_in[BUFSIZE];
  while ((taille = lire_nb(sock, buff_in)) > 0) {
    sscanf(buff_in, "%hu", &guess);
    printf("Joueur courant a envoyé : %d\n", guess);
    char reponse[20];
    if (n < guess || n > guess) {
      tentatives--;
    }
    if (tentatives == 0)
      sprintf(reponse, "PERDU\n");
    else if (n < guess)
      sprintf(reponse, "MOINS %d\n", tentatives);
    else if (n > guess)
      sprintf(reponse, "PLUS %d\n", tentatives);
    else {
      sprintf(reponse, "GAGNE\n");
      gagne = 1;
    }
    ecrire_nb(sock, reponse);
    if (gagne || !tentatives) break;
  }
  printf("Fin de partie\n");

  close(sock);
}

void *game_1p_point(void *arg) {
  int *joueurs = (int *)arg;
  free(arg);
  game_1p(*joueurs);
  return NULL;
}

/**
 * serveur pour jeu 1 player avec 1 connexion à la fois
 */
int server_1p() {
    int serv_sock = socket(PF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(4242);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) != 0) {
        perror("Échec de bind");
        exit(-1);
    }

    if (listen(serv_sock, 5) != 0) { 
        perror("Échec de listen");
        exit(-1);
    }

    printf("Serveur en attente sur le port 4242...\n");

    while (1) {
        struct sockaddr_in addrclient;
        socklen_t size = sizeof(addrclient);
    
        int *sock_client = malloc(sizeof(int));
        if (sock_client == NULL) continue;

        *sock_client = accept(serv_sock, (struct sockaddr *)&addrclient, &size);

        if (*sock_client < 0) {
            perror("Échec de accept");
            free(sock_client);
            continue;
        } 
        
        pthread_t thread;
        if (pthread_create(&thread, NULL, game_1p_point, sock_client) != 0) {
            perror("Erreur création thread");
            close(*sock_client);
            free(sock_client);
            continue;
        }

        pthread_detach(thread);

        char nom_dst[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &addrclient.sin_addr, nom_dst, sizeof(nom_dst));
        printf("Nouveau client : %s via socket %d\n", nom_dst, *sock_client);
        
    }

    close(serv_sock);
    return 0;
}
