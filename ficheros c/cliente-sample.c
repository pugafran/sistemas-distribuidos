#include <sys/socket.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <unistd.h> 
#include <arpa/inet.h> 
#include <stdio.h>

int main(int argc, char* argv[]) { 
	
	int sock_datos;
	struct sockaddr_in d_serv; char buffer[200];
	int recibidos;
	sock_datos = socket(PF_INET, SOCK_STREAM, 0); 
	d_serv.sin_family = AF_INET; 
	d_serv.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	d_serv.sin_port = htons(7890); connect(sock_datos, (struct sockaddr *)&d_serv, sizeof(d_serv)); 
	recibidos = recv(sock_datos, buffer, 200, 0);
	printf("Recibidos %d bytes\n", recibidos); buffer[recibidos] = 0; // Añadir terminador 
	printf("Mensaje: %s\n", buffer); close(sock_datos);
	
	return 0; 
}
