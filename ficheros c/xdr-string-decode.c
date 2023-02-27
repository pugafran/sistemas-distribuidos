// xdr-lee-entero.c
#include <stdio.h>    // Para FILE*
#include <errno.h>    // para perror()
#include <stdlib.h>   // para exit()
#include <rpc/types.h>
#include <rpc/rpc.h> 
int main() {
int dato_leido;   // Dato a leer
char dato_temporal; // Variable temporal para almacenar el valor leído
FILE *fichero;    // Fichero de donde se leerá
XDR operacion;

fichero=fopen("datos.xdr", "r+");  // Abrir para "r+"ead y escribir
if (fichero==NULL) {              // Comprobar errores
    perror("Al abrir fichero"); 
    exit(1); 
}

// Inicializar variable operación para filtros subsiguientes
xdrstdio_create(&operacion, fichero, XDR_DECODE);

// Leer sobre la variable dato_leido
xdr_char(&operacion, &dato_temporal);     // Llamada al filtro. Lee y decodifica
dato_leido = (int)dato_temporal; // Asignar el valor leído a la variable dato_leido

// Terminado, labores finales "domésticas"
xdr_destroy(&operacion);   // Destruir la variable operacion
fclose(fichero);           // Cerrar fichero

// Imprimir el valor leido:
printf("Dato leido=%c\n", dato_leido);

    return 0;

}
