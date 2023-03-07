// Fichero: convierte-a-anyos.c
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

int main(int argc, char* argv[]) {
    int sock_dat, recibidos;
    struct sockaddr_in d_serv;
    socklen_t ldir = sizeof(d_serv);
    char buffer[50];
    unsigned long int numero;
    
    sock_dat = socket(PF_INET, SOCK_DGRAM, 0);
    d_serv.sin_family = AF_INET;
    d_serv.sin_addr.s_addr = inet_addr("129.6.15.28");
    d_serv.sin_port = htons(37);
    
    // Enviar datagrama vacio
    sendto(sock_dat, buffer, 0, 0, (struct sockaddr *) &d_serv, ldir);
    recibidos = recvfrom(sock_dat, &numero, sizeof(numero), 0, (struct sockaddr *) &d_serv, &ldir);
    buffer[recibidos] = 0; // Añadir terminador
    printf("Mensaje recibido: %s\n", buffer);

    printf("Valor recibido: %lu\n", numero); // lu -> long unsigned

    unsigned long int ctimeSegundos = numero - 2208988800;

    // Convertir segundos en años, minutos y segundos
    unsigned int anios = numero / 31536000; // 60 * 60 * 24 * 365
    numero = numero % 31536000;
    unsigned long int dias = numero / 86400; // 60 * 60 * 24
    numero = numero % 86400;
    unsigned long int horas = numero / 3600; // 60 * 60
    numero = numero % 3600;
    unsigned long int minutos = numero / 60;
    numero = numero % 60;

    // Mostrar resultados
    printf("Tiempo total: %u años, %u días, %u horas, %u minutos, %u segundos\n", anios, dias, horas, minutos, numero);
    printf("La fecha con ctime es: %s\n",ctime((time_t *) &ctimeSegundos));
    return 0;

}



