#include <stdio.h> // Para FILE*
#include <errno.h> // para perror()
#include <stdlib.h> // para exit()
#include <rpc/types.h>
#include <rpc/rpc.h>
#include "tipos.h"

int main() {
  Texto cadena=NULL;
  FILE *fichero; // Fichero donde se escribirá
  XDR operacion;

  fichero=fopen("Texto.dat", "r"); // Abrir para "r"ead
  if (fichero==NULL) { // Comprobar errores
	perror("Al abrir fichero");
	exit(1);
  }

  // Inicializar variable operacion para filtros subsiguientes
  xdrstdio_create(&operacion, fichero, XDR_DECODE);

  xdr_Texto(&operacion,(Texto *) &cadena);

  // Terminado, labores finales "domésticas"
  xdr_destroy(&operacion); // Destruir la variable operacion
  fclose(fichero); // Cerrar fichero
  printf("La cadena leida es: %s", &cadena);
  return 0;

}
