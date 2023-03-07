#include <stdio.h>
#include <errno.h> 
#include <stdlib.h> 
#include <rpc/types.h> 
#include <rpc/rpc.h> 

int main() {
// Para FILE*
// para perror()
// para exit()
int j = 2013; // Dato a escribir
int aux, c;
FILE *fichero; // Fichero donde se escribirá
XDR operacion;
fichero=fopen("basicos.dat", "w"); // Abrir para "w"rite 
if (fichero==NULL) { // Comprobar errores
    perror("Al abrir fichero");
    exit(1); 
}

//xxd basicos.dat

// Inicializar variable operacion para filtros subsiguientes
xdrstdio_create(&operacion, fichero, XDR_ENCODE);
printf("\nIntroduce un valor entero: ");
scanf("%d", &j);
printf("\nIntroduce un carácter: ");
aux=getchar();
c = (char) fgetc(stdin);
// Escribir la variable j en el fichero, en representacion externa
xdr_int(&operacion, &j); // Llamada al filtro. Codifica y guarda // Terminado, labores finales "domésticas" xdr_destroy(&operacion); // Destruir la variable operacion fclose(fichero); // Cerrar fichero
xdr_char(&operacion, &c); //Codificamos el valor de tipo char
return 0; 
}