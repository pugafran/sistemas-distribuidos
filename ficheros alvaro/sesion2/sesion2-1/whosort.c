/*
EPI GIJÓN
GRADO EN INGENIERIA INFORMATICA
SISTEMAS DISTRIBUIDOS - CURSO 3º
MATERIAL DE LA ASIGNATURA
-------------------------
MECANISMO   : PIPES
FICHERO     : whosort.c
DESCRIPCION : Implementacion del proceso de usuario who | sort empleando
pipes.
*/
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(void)
{
  pid_t pid;
  int fds[2];	//  array de eneteros de dos posiciones
  		// donde van a quedar los descriptores
		// de los extremos de lectura y escritura del pipe
  pipe(fds);          /*Crea un pipe */
  /* El primer hijo reconecta su entrada standard (stdin) al flujo de
  salida del pipe y cierra su descriptor de la entrada del pipe */
  if ((pid=fork())<0)
  {
	perror("No pudimos clonarnos para generar el primer hijo");
	exit(1);
  }
  else if (pid  == 0) { // retorno del fork en el primer hijo
    // duplicamos los extremos de salida del pipe
    // en la entrada estandar (posicion 0 de la tabla de descriptores)
    dup2(fds[0], 0);
    close(fds[1]); // cierro el extremo del pipe que no uso
    execlp("sort", "sort", NULL);
  }
  /* El segundo hijo reconecta su salida standard (stdout) a la entrada
  del pipe y cierra el descriptor de la salida del pipe */
  else if ( (pid=fork()) < 0) { // nos intentamos clonar una segunda vez
  	perror("No pudimos clonarnos para generar el segundo hijo");
      	exit(1);
	}
 else if(pid == 0)
 {	
    dup2(fds[1], 1); // Duplicamos los datos del extremo de entrada
    		     // del pipe en el descriptor correspondiente a 
		     // la salida estandar (posicion 1 de la tabla 
		     // de descriptores)
    close(fds[0]); // cierro el extremo que no vamos a usar
    execlp("who", "who", NULL);
  }
  /*El padre cierra ambos descriptores del pipey espera la finalizacion
  de sus hijos */
  else {
    close(fds[0]);
    close(fds[1]);
    wait(0);
    wait(0);
  }
  return 1;
}
