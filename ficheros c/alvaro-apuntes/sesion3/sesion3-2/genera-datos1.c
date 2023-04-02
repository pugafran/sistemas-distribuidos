#include <stdio.h> // Para FILE*
#include <errno.h> // para perror()
#include <stdlib.h> // para exit()
#include <rpc/types.h>
#include <rpc/rpc.h>
#include "tipos.h"

int main() {
  Texto cadena="Probando";
  int j; // Dato a escribir
  int aux;
  char c; // Dato a escribir
  FILE *fichero; // Fichero donde se escribirá
  XDR operacion;

  fichero=fopen("Texto.dat", "w"); // Abrir para "w"rite
  if (fichero==NULL) { // Comprobar errores
	perror("Al abrir fichero");
	exit(1);
  }

  // Inicializar variable operacion para filtros subsiguientes
  xdrstdio_create(&operacion, fichero, XDR_ENCODE);

  xdr_Texto(&operacion,(Texto *) &cadena);

  // Terminado, labores finales "domésticas"
  xdr_destroy(&operacion); // Destruir la variable operacion
  fclose(fichero); // Cerrar fichero
  return 0;

}
