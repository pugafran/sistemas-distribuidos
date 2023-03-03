#include <stdio.h>
#include <arpa/inet.h> // incluir para utilizar las funciones htons y htonl

int main() {
    unsigned short short_num = 0x1234;
    unsigned int long_num = 0x12345678;

    // Convertir de host a network
    unsigned short network_short = htons(short_num);
    unsigned int network_long = htonl(long_num);

    printf("Número corto original: 0x%04x\n", short_num);
    printf("Número corto en network byte order: 0x%04x\n", network_short);
    printf("Número largo original: 0x%08x\n", long_num);
    printf("Número largo en network byte order: 0x%08x\n", network_long);

    // Convertir de network a host
    unsigned short host_short = ntohs(network_short);
    unsigned int host_long = ntohl(network_long);

    printf("Número corto en host byte order: 0x%04x\n", host_short);
    printf("Número largo en host byte order: 0x%08x\n", host_long);

    return 0;
}

