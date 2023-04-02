#include <stdio.h> // Para FILE*
#include <errno.h> // para perror()
#include <stdlib.h> // para exit()
#include <rpc/types.h>
#include <rpc/rpc.h>

int main() {
  int j; // Dato a escribir
  int aux;
  char c; // Dato a escribir
  FILE *fichero; // Fichero donde se escribirá
  XDR operacion;

  fichero=fopen("basicos.dat", "w"); // Abrir para "w"rite
  if (fichero==NULL) { // Comprobar errores
	perror("Al abrir fichero");
	exit(1);
  }

  // Inicializar variable operacion para filtros subsiguientes
  xdrstdio_create(&operacion, fichero, XDR_ENCODE);
  printf("Introduce una valor entero: ");
  scanf("%d", &j);
  aux=getchar(); // Consumo el retorno de carro
  printf("Introduce un caracter: ");
  c=(char)fgetc(stdin);

  // Escribir la variable j en el fichero, en representacion externa
  xdr_int(&operacion, &j); // Llamada al filtro. Codifica el entero
  xdr_char(&operacion, &c);  // Codificamos el valor de tipo char
  // Terminado, labores finales "domésticas"
  xdr_destroy(&operacion); // Destruir la variable operacion
  fclose(fichero); // Cerrar fichero
  return 0;

}
