#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <sched.h>

// Archivos de cabecera para manipulación de sockets
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main(int argc, char *argv[]){

    if (argc != 6) {
        fprintf(stderr, "El número de argumentos es incorrecto.\n");
        fprintf(stderr, "Uso: %s <num_puerto> <t|u> <tam_cola> <num_hilos_aten> <num_hilos_work>\n", argv[0]);
        exit(1);
    }

    // Extraer los argumentos y validar sus valores
    int num_puerto = atoi(argv[1]);
    if (num_puerto < 1024 || num_puerto > 65535) {
        fprintf(stderr, "El número de puerto debe estar entre 1024 y 65535.\n");
        exit(1);
    }

    char tipo_socket = * argv[2];
    if (tipo_socket != 't' && tipo_socket != 'u') {
        fprintf(stderr, "El tipo de socket debe ser 't' o 'u'.\n");
        exit(1);
    }

    int tam_cola = atoi(argv[3]);
    if (tam_cola <= 0) {
        fprintf(stderr, "El tamaño de la cola debe ser un número positivo.\n");
        exit(1);
    }

    int num_hilos_aten = atoi(argv[4]);
    if (num_hilos_aten <= 0) {
        fprintf(stderr, "El número de hilos de atención debe ser un número positivo.\n");
        exit(1);
    }

    int num_hilos_work = atoi(argv[5]);
    if (num_hilos_work <= 0) {
        fprintf(stderr, "El número de hilos trabajadores debe ser un número positivo.\n");
        exit(1);
    }

	return 0;



}
