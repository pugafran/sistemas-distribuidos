#include <stdio.h> // Para FILE*
#include <errno.h> // para perror()
#include <stdlib.h> // para exit()
#include <rpc/types.h>
#include <rpc/rpc.h>
#include "tipos.h"

int main() {
  Resultado res;
  FILE *fichero; // Fichero donde se escribirá
  XDR operacion;

  fichero=fopen("Resultado.dat", "r"); // Abrir para "r"ead
  if (fichero==NULL) { // Comprobar errores
	perror("Al abrir fichero");
	exit(1);
  }

  // Inicializar variable operacion para filtros subsiguientes
  xdrstdio_create(&operacion, fichero, XDR_DECODE);
 
  res.Resultado_u.error=NULL;
  xdr_Resultado(&operacion, (Resultado *) &res);


  switch(res.caso){
	  case 1: printf("El valor entero era: %d\n: ",res.Resultado_u.n);
		  break;
	  case 2: printf("El valor real era: %f\n: ",res.Resultado_u.x);
		  break;
	  case 3: printf("La cadena era: %s\n", res.Resultado_u.error);
		  break;
	  default:
		  printf("Valor erroneo del selector\n");
  }



  // Terminado, labores finales "domésticas"
  xdr_destroy(&operacion); // Destruir la variable operacion
  fclose(fichero); // Cerrar fichero
  return 0;

}
