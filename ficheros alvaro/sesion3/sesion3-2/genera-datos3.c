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

  fichero=fopen("Resultado.dat", "w"); // Abrir para "w"rite
  if (fichero==NULL) { // Comprobar errores
	perror("Al abrir fichero");
	exit(1);
  }

  // Inicializar variable operacion para filtros subsiguientes
  xdrstdio_create(&operacion, fichero, XDR_ENCODE);
  printf("Menu: \n");
  printf("1- Entero\n");
  printf("2- Real\n");
  printf("3- Texto\n");
  printf("Elige una opcion: ");

  scanf("%d",&res.caso);
  switch(res.caso){
	  case 1: printf("Introduce un valor entero: ");
		  scanf("%d", &res.Resultado_u.n);
		  break;
	  case 2: printf("Introduce un calor real: ");
		  scanf("%f", &res.Resultado_u.x);
		  break;
	  case 3: printf("Introduce una cadena: ");
		  res.Resultado_u.error=malloc(sizeof(char)*100);
		  getchar(); // consumimos el retorno de carro del buffer de teclado
		  fgets(res.Resultado_u.error,99,stdin);
		  break;
  }

  xdr_Resultado(&operacion,(Resultado *) &res);

  // Terminado, labores finales "domésticas"
  xdr_destroy(&operacion); // Destruir la variable operacion
  fclose(fichero); // Cerrar fichero
  return 0;

}
