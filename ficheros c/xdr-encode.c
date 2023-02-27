// xdr-escribe-entero.c
#include <stdio.h>    // Para FILE*
#include <errno.h>    // para perror()
#include <stdlib.h>   // para exit()
#include <rpc/types.h>
#include <rpc/rpc.h> 
int main() {
    int j = 69420;     // Dato a escribir
    FILE *fichero;    // Fichero donde se escribirá
    XDR operacion;

    fichero=fopen("datos.xdr", "w");  // Abrir para "w"rite
    if (fichero==NULL) {              // Comprobar errores
        perror("Al abrir fichero"); 
        exit(1); 
    }

    // Inicializar variable operacion para filtros subsiguientes
    xdrstdio_create(&operacion, fichero, XDR_ENCODE);

    // Escribir la variable j en el fichero, codificada en representacion externa
    xdr_int(&operacion, &j);     // Llamada al filtro. Codifica y guarda

    // Terminado, labores finales "domésticas"
    xdr_destroy(&operacion);   // Destruir la variable operacion
    fclose(fichero);           // Cerrar fichero
    return 0;
}
