#include <arpa/inet.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <time.h>

#define BUFFSIZE 1024

// verrou
pthread_mutex_t verrou = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;

int reponse;
int max_tent = 10;
int joueurs_co = 0;
int maxi;
int rang = 1;

int lire_nb(int sock, char *buf)
{
    int taille, ind = 0;
    do
    {
        if ((taille = recv(sock, buf + ind, BUFFSIZE - 1 - ind, 0)) < 0)
        {
            perror("recv");
            exit(1);
        }
        ind += taille;
    } while (ind < BUFFSIZE - 1 && taille != 0 && !memchr(buf, '\n', ind));

    if (ind > BUFFSIZE)
    {
        fprintf(stderr, "erreur format message recu\n");
        exit(1);
    }
    buf[ind] = 0;

    return ind;
}

int ecrire_nb(int sock, char *buf)
{
    int lg = 0, lu;
    do
    {
        if ((lu = send(sock, buf, strlen(buf), 0)) <= 0)
        {
            perror("send");
            exit(1);
        }
        lg += lu;
    } while (lg < strlen(buf));

    return lg;
}

int jeu(int sock){
    int n = reponse;
    printf("nb mystere pour partie socket %d = %d\n", sock, n);
    
    unsigned short int guess;
    int taille = 0;
    int tentatives = 20;
    int gagne = 0;
    char buff_in[BUFFSIZE];
    while ((taille = lire_nb(sock, buff_in)) > 0)
    {
        sscanf(buff_in, "%hu", &guess);
        printf("Joueur courant a envoyé : %d\n", guess);
        char message[20];
        if (n < guess || n > guess)
        {
            tentatives--;
        }
        if (tentatives == 0)
            sprintf(message, "PERDU\n");
        else if (n < guess)
            sprintf(message, "MOINS %d\n", tentatives);
        else if (n > guess)
            sprintf(message, "PLUS %d\n", tentatives);
        else
        {
            sprintf(message, "GAGNE\n");
            gagne = 1;
        }
        ecrire_nb(sock, message);
        if (gagne || !tentatives)
            break;
    }
    printf("Fin de partie\n");
}

void *serve(void *arg)
{
    int sock = *((int *)arg);
    free(arg);

    // attente
    pthread_mutex_lock(&verrou);
    joueurs_co++;

    if (joueurs_co < maxi)
    {
        while (joueurs_co < maxi)
        {
            pthread_cond_wait(&condition, &verrou);
        }
    }
    else
    { // dernier joueur il signale aux autres que c bon
        pthread_cond_broadcast(&condition);
    }
    pthread_mutex_unlock(&verrou);

    // appel fonction jeu
    jeu(sock);
    close(sock);
    return NULL;
}

int main(int argc, char **argv)
{
    maxi = atoi(argv[1]);

    srandom(time(NULL));
    reponse = random() % 100;
    printf("réponse: %d\n", reponse);

    // création sockat serveur
    int sock = socket(PF_INET6, SOCK_STREAM, 0);
    if (sock < 0)
        exit(1);

    // struct pour maniouler les ipv4
    struct sockaddr_in6 adrsock;
    memset(&adrsock, 0, sizeof(adrsock));
    adrsock.sin6_family = AF_INET6;
    adrsock.sin6_port = htons(2121);
    adrsock.sin6_addr = in6addr_any;

    // lier les 2
    int r = bind(sock, (struct sockaddr *)&adrsock, sizeof(adrsock));
    if (r < 0)
        exit(0);

    // commencer à écouter
    int l = listen(sock, 0);

    pthread_t threads[maxi];

    // accepter les joueurs dans un thread par joueur
    for (int i = 0; i < maxi; i++)
    {

        struct sockaddr_in6 adr_client; 
        socklen_t len_client = sizeof(adr_client);

        // un malloc par client
        int *sockclient = malloc(sizeof(int));
        *sockclient = accept(sock, (struct sockaddr *)&adr_client, &len_client);

        if (pthread_create(&threads[i], NULL, serve, sockclient) != 0)
        {
            perror("thread");
        }

        char nom_dst[INET6_ADDRSTRLEN];
        inet_ntop(AF_INET6, &adr_client.sin6_addr, nom_dst, sizeof(nom_dst));
        printf("Nouveau client : %s via socket %d\n", nom_dst, *sockclient);
    }

    for (int i = 0; i < maxi; i++)
    {
        pthread_join(threads[i], NULL);
    }
    exit(0);
}