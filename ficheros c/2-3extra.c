#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#define MAX_PROCESOS 5 // Número máximo de procesos simultáneos permitidos

int contador_procesos = 0;

void handler(int sig) {
    int status;
    pid_t pid;
    
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        printf("Proceso hijo %d finalizado.\n", pid);
        // Decrementar el contador de procesos activos
        --contador_procesos;
    }
}

int main() {
    contador_procesos = MAX_PROCESOS;
    pid_t pid;

    // Registrar el handler para la señal SIGCHLD
    signal(SIGCHLD, handler);

    while (1) {
        // Esperar a que llegue un cliente
        // ...

        // Si el contador de procesos activos es mayor a cero
        if (contador_procesos > 0) {
            // Lanzar un proceso hijo
            pid = fork();

            if (pid < 0) {
                perror("Error en fork()");
                exit(EXIT_FAILURE);
            } else if (pid == 0) {
                // Código del proceso hijo
                // ...
                exit(EXIT_SUCCESS);
            } else {
                // Código del proceso padre
                // Decrementar el contador de procesos activos
                --contador_procesos;
            }
        } else {
            // Esperar a que alguno de los procesos hijos finalice
            // ...
        }
    }

    return 0;
}

