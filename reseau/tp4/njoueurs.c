#include <arpa/inet.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <time.h>

#define BUFFSIZE 1024

//verrou
pthread_mutex_t verrou = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;

int reponse;
int max_tent = 10;
int joueurs_co = 0;
int maxi;
int rang = 1;


void *serve(void *arg){
    int sock = *((int*)arg);
    free(arg);

    //attente
    pthread_mutex_lock(&verrou);
    joueurs_co ++;

    if (joueurs_co < maxi){
        while(joueurs_co < maxi){
            pthread_cond_wait(&condition, &verrou);
        }
    }
    else{ //dernier joueur il signale aux autres que c bon
        pthread_cond_broadcast(&condition);
    }
    pthread_mutex_unlock(&verrou);

    //appel fonction jeu
    jeu(sock);
    close(sock);
    return NULL;
}

int jeu(int sock){
    senf(sock, "DEBUT\n", 6, MSG_NOSIGNAL);

}


int main(int argc, char **argv){
    maxi = atoi(argv[1]);

    srandom(time(NULL));
    reponse = random() % 100;
    printf("réponse: %d\n", reponse);

    //création sockat serveur
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock < 0) exit(1);

    //struct pour maniouler les ipv4
    struct sockaddr_in adrsock;
    memset(&adrsock, 0, sizeof(adrsock));
    adrsock.sin_family = AF_INET;
    adrsock.sin_port = htons(2121);
    adrsock.sin_addr.s_addr = htonl(INADDR_ANY);

    //lier les 2
    int r = bind(sock, (struct sockaddr *) &adrsock, sizeof(adrsock));
    if (r < 0) exit(0);

    //commencer à écouter
    int l = listen(sock, 0);

    pthread_t threads[maxi];

    //accepter les joueurs dans un thread par joueur
    for (int i = 0; i < maxi; i++){
        //un malloc par client
        int *sockclient = malloc(sizeof(int));
        *sockclient = accept(sock, NULL, NULL);
        
        if(pthread_create(&threads[i], NULL, serve, sockclient) != 0){
            perror("thread");
        }

        char nom_dst[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &adrsock.sin_addr, nom_dst, sizeof(nom_dst));
        printf("Nouveau client : %s via socket %d\n", nom_dst, *sockclient);
    }
}