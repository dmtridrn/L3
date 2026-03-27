#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(){
    uint32_t test = 0x01020304;
    unsigned char *bytes = (unsigned char*)&test;
    for(int i = 0; i<4; i++){
        printf("%i", bytes[i]);
    }
}