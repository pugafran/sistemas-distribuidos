#include <stdio.h> // Para FILE*
#include <errno.h> // para perror()
#include <stdlib.h> // para exit()
#include <rpc/types.h>
#include <rpc/rpc.h>
#include "tipos.h"

int main() {
  Persona alumno;
  FILE *fichero; // Fichero donde se escribirá
  XDR operacion;

  fichero=fopen("Persona.dat", "r"); // Abrir para "w"rite
  if (fichero==NULL) { // Comprobar errores
	perror("Al abrir fichero");
	exit(1);
  }

  // Inicializar variable operacion para filtros subsiguientes
  xdrstdio_create(&operacion, fichero, XDR_DECODE);
  alumno.nombre=NULL;
  xdr_Texto(&operacion,(Persona *) &alumno);

  printf("El nombre del alumno es: %s\n" ,&alumno.nombre);
  printf("La edad del alumno es: %d\n", &alumno.edad);

  // Terminado, labores finales "domésticas"
  xdr_destroy(&operacion); // Destruir la variable operacion
  fclose(fichero); // Cerrar fichero
  return 0;

}
