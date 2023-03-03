#include <stdio.h>

int main() {
    unsigned int x = 0x01020304;
    unsigned char *c = (unsigned char*) &x;

    printf("El valor de x es: 0x%x\n", x);
    
    if (*c == 0x01) {
        printf("La arquitectura de la computadora es big-endian. (0x40302010)\n");
    } else {
        printf("La arquitectura de la computadora es little-endian. (0x01020304)\n");
        printf("Si lo pasamos a Big Endian con htonl queda como: %08x\n", htonl(x));
    }
    
    return 0;
}

