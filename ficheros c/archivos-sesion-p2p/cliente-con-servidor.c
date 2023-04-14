// Este cliente implementa la comunicacion entre peers por el protocolo UDP
// Usa select para multiplexar su atención entre el teclado y el socket p2p

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "protocolo.h"
#include <sys/select.h>


#define MAX_TAM_LINEA   500
#define MAX_TAM_MENSAJE 500
#define MAX_TAM_NICK    10

char *nick;                 // Para enviarlo en cada mensaje

// Estas funciones están implementadas después de main()
void leer_y_procesar_teclado(int socketUDP, int socketTCP);
void recibir_y_mostrar_mensaje(int socketUDP, int socketTCP);

int main(int argc, char *argv[])
{
    int socketUDP, puerto;  // Para el socket entre peers
    struct sockaddr_in dirUDP;

    int socketTCP, puertoServidor;
    struct sockaddr_in dirTCP;

    int teclado = 0;        // Descriptor de la entrada estandar

    // Para el select
    fd_set escucha;
    int max;
    int resultado;

    // Las siguientes variables contendrán la IP y puerto del peer
    // al que enviar los mensajes
    char *ip_peer = NULL;
    char *ipServidor = NULL;
    int  puerto_peer = 0;

    /***** Comprobación de argumentos *****/
    if (argc != 5)
    {
        printf("Uso: %s <puerto> <nick> <ip servidor> <puerto servidor>\n", argv[0]);
        exit(2);
    }
    nick = argv[2];
    // Truncar nick si es necesario
    if (strlen(nick) >= MAX_TAM_NICK - 1)
        nick[MAX_TAM_NICK - 1] = 0;
    
    //TODO: Comprobar puerto
    puerto = atoi(argv[1]);
    puertoServidor = atoi(argv[4]);

    const char *ipServidor = argv[3];
    //struct in_addr ip_str_addr;

    if ((socketTCP = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Al crear el socket");
        exit(EXIT_FAILURE);
    }

    dirTCP.sin_family = AF_INET;
    dirTCP.sin_addr.s_addr = htonl(argv[3]);
    dirTCP.sin_port = htons(puertoServidor);
    
    //complete TCP conection
    if (connect(socketTCP, (struct sockaddr *) &dirTCP, sizeof(struct sockaddr_in)) < 0) {
        perror("Al conectar con el servidor");
        exit(EXIT_FAILURE);
    }

    sendByte(socketTCP, JOIN_CMD);

    //receive the message of server
    if (readByte(socketTCP) != CMD_OK)
    {
        perror("El nick ya estaba registrado, u otros problemas");
        exit(EXIT_FAILURE);
    }

    close(socketTCP);


    

    /***** Inicialización del socket ****/
    // Creamos el socket UDP en el puerto que se le pasa por linea de comandos
    socketUDP = socket(PF_INET, SOCK_DGRAM, 0);
    if (socketUDP == -1)
    {
        perror("Al crear el socket UDP");
        exit(1);
    }
    dirUDP.sin_family = AF_INET;
    dirUDP.sin_addr.s_addr = htonl(INADDR_ANY);
    dirUDP.sin_port = htons(puerto);
    resultado = bind(socketUDP, (struct sockaddr *) &dirUDP, sizeof(struct sockaddr_in));
    if (resultado < 0)
    {
        perror("Al hacer bind");
        //echo $?
        exit(3);
    }

    printf("Usa el comando /CHAT <ip> <puerto> para indicar el destino de tus mensajes\n");
    printf("El texto que escribas después se enviará a ese contacto\n\n");
    printf("En cualquier momento puedes poner /CHAT <ip> <puerto> de nuevo\n");
    printf("para cambiar a un nuevo contacto.\n\n");

    // Y entramos en el bucle de espera
    printf("%s> ", nick);
    while (1)
    {
        // Imprimir un prompt para invitar a escribir
        fflush(stdout);        // Para que lo saque ya, pues no finaliza con \n

        // Esperar en select a que el usuario escriba algo, o a que algo llegue
        // por el socket UDP

        /***************************************************/
        /* A RELLENAR                                      */
        /* Llamada a select, previa inicialización         */
        /* de las variables necesarias                     */
        /***************************************************/

        FD_ZERO(&escucha);

        //Metemos en el conjunto de descriptores
        FD_SET(teclado,&escucha);
        FD_SET(socketUDP,&escucha);

        //La máxima entrada + 1, como poco socketUDP será 3
        select(socketUDP + 1, &escucha, 0, 0, 0); // o NULL,NULL,NULL

        // Al salir es que algo ha ocurrido
        if (FD_ISSET(socketUDP, &escucha))
        {
            recibir_y_mostrar_mensaje(socketUDP, socketTCP);
        }

        if (FD_ISSET(teclado, &escucha))
        {
            leer_y_procesar_teclado(socketUDP, socketTCP);
        }
    }
}

void recibir_y_mostrar_mensaje(int socketUDP, int socketTCP)
{
    char buff[MAX_TAM_MENSAJE];
    int recibidos;

    recibidos = recvfrom(socketUDP, buff, MAX_TAM_MENSAJE, 0, NULL, NULL);
    if (recibidos < 0) return; // Ignoramos silenciosamente errores
    //Para que pare
    buff[recibidos] = 0;
    printf("\n**|%s|\n", buff);
}

void leer_y_procesar_teclado(int socketUDP, int socketTCP, int puertoServidor, char *ipServidor)
{
    char linea[MAX_TAM_LINEA];
    char cmd[MAX_TAM_LINEA];
    static char ip_destino[25] = "No asignada";
    static int  puerto_destino = 0;
    static struct sockaddr_in dir_destino;
    char *mensaje_a_enviar;
    int i;

    // Leer la línea
    fgets(linea, MAX_TAM_LINEA - MAX_TAM_NICK, stdin);
    // Eliminarle el retorno de carro o espacios al final
    for (i = strlen(linea) - 1; i >= 0; i--)
    {
        if (isspace(linea[i]))
            linea[i] = 0;
        else
            break;
    }
    // Sacar un nuevo prompt
    printf("%s> ", nick);

    // Ver si es un comando
    if (linea[0] == '/')
    {
        // Comienza por /, en ese caso hay que procesarlo. 
        // Lo más fácil es leer sus contenidos con sscanf
        
        //Primer token
        sscanf(linea, "%s", cmd);

        /*******************************************************/
        /* A RELLENAR                                          */
        /* En función del valor encontrado en cmd, realizamos  */
        /* la acción apropiada                                 */
        /*******************************************************/

        if (strcmp(cmd,"/CHAT") == 0){

            socketTCP = CrearSocketDatosTCP();
            CrearSocketServidorTCP(socketTCP);
            Conectar(socketTCP, ipServidor, puertoServidor);
            sendShort(socketTCP, QUERY_CMD);

            //Cambiamos al destinatario de nuestros mensajes
            sscanf(linea, "%s %s %d", cmd, &ip_destino, &puerto_destino);
            
            dir_destino.sin_family = AF_INET;
            dir_destino.sin_port = htons(puerto_destino);
            dir_destino.sin_addr.s_addr = inet_addr(ip_destino);
        }

        else if (strcmp(cmd,"/QUIT") == 0)
        {
            exit(0);
        }

        else{

            printf("Error");
            exit(1);
        }
        

    }
    else      // Si la linea no comienza por /, es un mensaje a enviar al peer
    {
        // Hay que enviarlo a la ip y puertos antes asignados, 
        // pero antes comprobamos si efectivamente se asignaron
        // antes estos valores
        if (strcmp(ip_destino, "No asignada") == 0)
        {
            printf("ERROR: antes de enviar mensaje debes usar el comando\n");
            printf("/CHAT <ip> <puerto>\n");
            return;
        }
        // Si todo va bien, enviamos el mensaje, 
        // precedido por el nick del usuario

        /*******************************************************/
        /* A RELLENAR                                          */
        /* Crear un buffer con el mensaje a enviar y enviarlo  */
        /*******************************************************/

        mensaje_a_enviar = (char *) malloc(sizeof(char) * MAX_TAM_MENSAJE);

        sprintf(mensaje_a_enviar, "%s> %s", nick, linea);

        sendto(socketUDP, mensaje_a_enviar, strlen(mensaje_a_enviar), 0, (struct sockaddr *) &dir_destino, sizeof(dir_destino));
        free(mensaje_a_enviar);
        return;

    }
}
