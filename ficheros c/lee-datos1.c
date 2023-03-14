#include <stdio.h>
#include <errno.h> 
#include <stdlib.h> 
#include <rpc/types.h> 
#include <rpc/rpc.h> 
#include "tipos.h"

int main() {
// Para FILE*
// para perror()
// para exit()
int j = 2013; // Dato a escribir
int aux, c;
Texto cadena = NULL;
FILE *fichero; // Fichero donde se escribirá
XDR operacion;
fichero=fopen("texto.dat", "r"); // Abrir para "w"rite 
if (fichero==NULL) { // Comprobar errores
    perror("Al abrir fichero");
    exit(1); 
}

//xxd basicos.dat

// Inicializar variable operacion para filtros subsiguientes
xdrstdio_create(&operacion, fichero, XDR_DECODE);

xdr_Texto(&operacion, (Texto *) &cadena);
xdr_destroy(&operacion);
printf("La cadena es %s", cadena);
fclose(fichero);

return 0; 
}