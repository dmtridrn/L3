#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

int main(){
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adrsock;
    memset(&adrsock, 0, sizeof(adrsock));
    adrsock.sin_family = AF_INET;
    adrsock.sin_port = htons(2112);
    inet_pton(AF_INET, "127.0.0.1", &adrsock.sin_addr);

    connect(sock, (struct sockaddr*)&adrsock, sizeof(adrsock));

    int min = 0;
    int max = 65535;
    uint8_t reception[2]; //reception métisse
    uint16_t envoi; //envoi métisse

    for(int i = 0; i<20; i++){
        //envoi guess métisse
        uint16_t guess = (max+min)/2;
        printf("j'envoie un métisse %d\n", guess);
        envoi = htons(guess);
        send(sock, &envoi, 2, 0);

        //reception réponse
        recv(sock, reception, 2,0);
        printf("serveur métissé répond: %d\n", reception);

        if(reception[1] == 0){
            max = guess - 1;
        }
        else if(reception[1] == 1){
            min = guess + 1;
        }
        else{
            printf("ayooo g perdu ou gagné\n");
            break;
        }
    }
    close(sock);
}