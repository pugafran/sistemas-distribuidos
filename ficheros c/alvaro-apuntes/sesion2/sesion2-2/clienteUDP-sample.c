#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]) {
	int sock_dat, recibidos;
	struct sockaddr_in d_serv; 
	socklen_t ldir = sizeof(d_serv); 
	char buffer[50];
	sock_dat = socket(PF_INET, SOCK_DGRAM, 0); d_serv.sin_family = AF_INET; d_serv.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	d_serv.sin_port = htons(7890);
	// Enviar datagrama vacio
	sendto(sock_dat, buffer, 0, 0, (struct sockaddr *) &d_serv, ldir); recibidos = recvfrom(sock_dat, buffer, 50, 0,
	(struct sockaddr *) &d_serv, &ldir); buffer[recibidos] = 0; // Añadir terminador
	printf("Mensaje recibido: %s\n", buffer); 
}
