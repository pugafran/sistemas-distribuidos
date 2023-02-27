#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_PROCESOS_SIMULTANEOS 2

void atrapa_sigchld(int s){
    wait(0);
    return;
}

int main(){
    int sock_pasivo, sock_datos;
    struct sockaddr_in d_local;
    char buffer[100];
    int leidos;
    pid_t pid;
    int contador_procesos = 0;

    signal(SIGCHLD, atrapa_sigchld);

    sock_pasivo = socket(PF_INET, SOCK_STREAM, 0);

    d_local.sin_family = AF_INET;

    d_local.sin_addr.s_addr = htonl(INADDR_ANY);

    d_local.sin_port = htons(7890);

    bind(sock_pasivo, (struct sockaddr *)&d_local, sizeof(d_local));

    listen(sock_pasivo, SOMAXCONN);

    while(1){
        if (contador_procesos < MAX_PROCESOS_SIMULTANEOS) {
            sock_datos = accept(sock_pasivo, 0, 0);

            if ((pid = fork()) < 0){
                perror("Error en fork");
                exit(1);
            }

            else if(pid == 0){
                printf("Soy el proceso hijo (%d) antes del while\n", getpid());

                while ((leidos = read(sock_datos, buffer, sizeof(buffer))) > 0){
                    printf("Soy el proceso hijo (%d) antes del write\n", getpid());
                    write(sock_datos, buffer, leidos);
                    printf("Soy el proceso hijo (%d) después del write\n", getpid());
                }

                close(sock_datos);

                printf("Soy el proceso hijo (%d) antes de terminar\n", getpid());
                exit(0);
            }

            else {
                printf("Soy el proceso padre (%d) antes de incrementar el contador\n", getpid());
                contador_procesos++;
                printf("Contador de procesos: %d\n", contador_procesos);
                close(sock_datos);
            }
        }

        else {
            printf("[Número máximo de procesos simultáneos alcanzados]\n");
            printf("Soy el proceso padre (%d) esperando a que algún hijo termine\n", getpid());
            wait(0);
            contador_procesos--;
            printf("Contador de procesos: %d\n", contador_procesos);
        }
    }
}
