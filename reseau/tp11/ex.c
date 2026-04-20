#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <hostname>\n", argv[0]);
        return 1;
    }

    SSL_library_init();
    SSL_load_error_strings(); 

    SSL_CTX *ctx = SSL_CTX_new(TLS_client_method());
    int sock = socket(AF_INET, SOCK_STREAM, 0); 

    struct hostent *host = gethostbyname(argv[1]);
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(443); 
    memcpy(&addr.sin_addr.s_addr, host->h_addr, host->h_length);

    connect(sock, (struct sockaddr *)&addr, sizeof(addr));

    SSL *ssl = SSL_new(ctx);
    SSL_set_tlsext_host_name(ssl, argv[1]);
    SSL_set_fd(ssl, sock); 
    SSL_connect(ssl); 

    char request[1024];
    sprintf(request, "GET / HTTP/1.0\r\nHost: %s:443\r\nConnection: close\r\n\r\n", argv[1]);
    SSL_write(ssl, request, strlen(request)); 

    char buffer[4096];
    int n;
    while ((n = SSL_read(ssl, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[n] = '\0';
        printf("%s", buffer);
    }

    SSL_shutdown(ssl);
    close(sock); 
    SSL_free(ssl);
    SSL_CTX_free(ctx);

    return 0;
}