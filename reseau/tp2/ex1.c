#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(){
    uint32_t witness = 0x01020304;
    unsigned char *bytes = (unsigned char*)&witness;
    for(int i = 0; i<4; i++){
        printf("%i", bytes[i]);
    }
}