#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>


int main(){

int recibidos, sock_dat;

struct sockaddr_in d_local, d_cliente;

char buffer[100];

socklen_t ldir = sizeof(d_local);



sock_dat = socket(PF_INET, SOCK_DGRAM, 0);

d_local.sin_family = AF_INET;

d_local.sin_addr.s_addr = htonl(INADDR_ANY);

d_local.sin_port = htons(7890);

bind(sock_dat, (struct sockadrr *)&d_local, sizeof(d_local));


//listen(sock_pasivo, SOMAXCONN);

while(1){

recibidos = recvfrom(sock_dat, buffer, sizeof(buffer), 0, (struct sockaddr *)&d_cliente, &ldir);

	printf("Cliente desde %s (%d)\n)", inet_ntoa(d_cliente.sin_addr), ntohs(d_cliente.sin_port));
	sendto(sock_dat, buffer, recibidos, 0, (struct sockaddr *) &d_cliente, &ldir);
}

}
