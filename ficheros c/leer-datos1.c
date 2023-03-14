#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <rpc/types.h>
#include <rpc/xdr.h>
#include "tipos.h"

#define BUFSIZ 4096

int main() {
    Texto cadena;
    FILE *fichero;
    XDR operacion;
    char buffer[BUFSIZ];
    int bytes_leidos;

    fichero = fopen("texto.dat", "r");
    if (fichero == NULL) {
        perror("Al abrir fichero");
        exit(1);
    }

    xdrrec_create(&operacion, 1, BUFSIZ, (caddr_t)buffer, NULL, XDR_DECODE);
    bytes_leidos = fread(buffer, 1, BUFSIZ, fichero);
    if (!xdr_Texto(&operacion, &cadena)) {
        fprintf(stderr, "Error al decodificar la cadena\n");
        exit(1);
    }

    printf("Texto: %s\n", cadena);

    xdr_destroy(&operacion);
    fclose(fichero);
    return 0;
}
