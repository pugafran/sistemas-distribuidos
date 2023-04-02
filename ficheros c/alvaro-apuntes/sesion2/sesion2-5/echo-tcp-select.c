// Fichero: echo-tcp-udp-select.c
#include <stdio.h>       // printf()
#include <stdlib.h>      // exit()
#include <sys/socket.h>  // socket(), bind(), listen(), recv(), send(), etc
#include <arpa/inet.h>   // sockaddr_in
#include <errno.h>       // perror()
#include <sys/select.h>  // select() y fd_set
#include <unistd.h>      // close()


#define MAXCLIENTES 5  //Maximo de clientes conectados a admitir

int CrearSocketTCP(int puerto)
{
    int s;
    struct sockaddr_in dir;
    int r;

    s = socket(PF_INET, SOCK_STREAM, 0);
    if (s==-1) {
        perror("En socket TCP");
        exit(1);
    }
    dir.sin_family = AF_INET;
    dir.sin_port   = htons(puerto);
    dir.sin_addr.s_addr = htonl(INADDR_ANY);
    r = bind(s, (struct sockaddr *) &dir, sizeof(dir));
    if (r==-1) {
        perror("En bind TCP");
        exit(1);
    }
    r = listen(s, SOMAXCONN);
    if (r==-1) {
        perror("En listen");
        exit(1);
    }
    return s;
}

int CrearSocketUDP(int puerto)
{
    int s;
    struct sockaddr_in dir;
    int r;
    // -------------------------------
    // A completar por el alumno
    // -------------------------------

    s = socket(PF_INET, SOCK_DGRAM, 0);
    if (s==-1) {
        perror("En socket UDP");
        exit(1);
    }
    dir.sin_family = AF_INET;
    dir.sin_port   = htons(puerto);
    dir.sin_addr.s_addr = htonl(INADDR_ANY);
    r = bind(s, (struct sockaddr *) &dir, sizeof(dir));
    if (r==-1) {
        perror("En bind UDP");
        exit(1);
    }

    return s;
}

void dar_servicio_UDP(int s)
{
    // Lee un datagrama del socket s y lo reenvía a su origen
    struct sockaddr_in origen;
    socklen_t tamanio = sizeof(origen);
    char buffer[100];
    int leidos;

    leidos = recvfrom(s, buffer, 100, 0, (struct sockaddr *) &origen, &tamanio);
    sendto(s, buffer, leidos, 0, (struct sockaddr *) &origen, tamanio);
}


int dar_servicio_TCP(int s)
{
    // Lee datos del socket s y si lee distinto de cero, envia eco
    // Retorna el numero de datos leidos

   char buffer[100];
   int leidos;

   leidos = recv(s, buffer, 100, 0);
   if (leidos>0)
       send(s, buffer, leidos, 0);
   return leidos;
}

int max(int a, int b)
{
    // Devuelve el mayor entre a y b
    if (a>b) return a;
    else return b;
}

int buscar_maximo(int tcp, int *cli, int tam)
{
    // La funcion retorna el maximo entre el socket TCP y las posiciones
    // distintas de 0 del array de clientes

    int resultado = tcp;
    int i;

    for(i=0;i<tam;i++)
	if(cli[i]>resultado) resultado=cli[i];
    return resultado;
}

void inicializaClientes(int *cli,int tam){
	int i;
	for(i=0;i<tam;i++) cli[i]=0;
}

int buscarPosicionLibre(int *cli, int tam){
	int i;

	for(i=0;i<tam;i++)
		if(cli[i]==0) return i;

}


int main(int argc, char * argv[])
{
    int puerto;
    int s_tcp; // sockets "de escucha"
    int s_datos[MAXCLIENTES];      // Para la conexion TCP
    fd_set conjunto;  // Para select
    int    maximo;    // Para select
    int numClientes = 0; //Numero de clientes TCP activos
    int i;
    int pos;

    if (argc<2) {
        printf("Uso: %s puerto\n", argv[0]);
        exit(0);
    }

    puerto = atoi(argv[1]);  // El numero de puerto debe ser mayor que 1024 y menor que 49151
    s_tcp = CrearSocketTCP(puerto);
    inicializaClientes(s_datos,MAXCLIENTES);

    while (1) {  // Bucle infinito del servidor

        // Vaciar conjunto de descriptores a vigilar
        FD_ZERO(&conjunto);

	// Si el numero de clientes activos es menor que MAXCLIENTES
	// entonces vigilo el socket pasivo
	//

	if (numClientes < MAXCLIENTES) FD_SET(s_tcp, &conjunto);

	for(i=0;i<MAXCLIENTES;i++){
		if(s_datos[i] !=0) FD_SET(s_datos[i], &conjunto);  // Vigilar las posiciones distintas de cero, tienen un cliente conectado
	}


        maximo = buscar_maximo(s_tcp, s_datos, MAXCLIENTES);

        // Esperar a que ocurra "algo"
        select(maximo + 1, &conjunto, NULL, NULL, NULL);
        printf("Ha ocurrido algo\n");

        // Averiguar que ocurrió
        if((numClientes<MAXCLIENTES)&&(FD_ISSET(s_tcp,&conjunto)))
        {
            printf("Ha llegado un cliente al socket TCP\n");
	    pos=buscarPosicionLibre(s_datos, MAXCLIENTES);
            s_datos[pos] = accept(s_tcp, NULL, NULL);
	    numClientes++;
        }

	for(i=0;i<MAXCLIENTES;i++){
         if((s_datos[i]!=0)&&(FD_ISSET(s_datos[i],&conjunto)))
         {
            int n;
            printf("Han llegado datos por la conexión TCP\n");
            n = dar_servicio_TCP(s_datos[i]);
            if (n==0) {
                printf("El cliente TCP ha desconectado\n");
		close(s_datos[i]);
                s_datos[i] = 0;
		numClientes--;
            }
         }
	}
    } // del while(1)
    return 0;   // Nunca se ejecuta, pero para que el compilador no proteste
} // de main()
