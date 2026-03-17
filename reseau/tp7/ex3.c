#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(){
    
    char paquet[] = {0,1,'f','i','l','e', 0, 'o','c','t','e','t', 0};
    //             opcode    nomfich                mode        
    
    
    
}