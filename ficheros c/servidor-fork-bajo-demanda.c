#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

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


signal(SIGCHLD, atrapa_sigchld);

sock_pasivo = socket(PF_INET, SOCK_STREAM, 0);

d_local.sin_family = AF_INET;

d_local.sin_addr.s_addr = htonl(INADDR_ANY);

d_local.sin_port = htons(7890);

bind(sock_pasivo, (struct sockadrr *)&d_local, sizeof(d_local));

listen(sock_pasivo, SOMAXCONN);
printf("Soy el proceso padre (%d) antes del while\n", getpid());
while(1){
printf("Soy el proceso padre (%d) antes del accept\n", getpid());

sock_datos = accept(sock_pasivo, 0, 0);

//Error de clonación, lo hacemos nosotros mismos:
if ((pid = fork()) < 0){
	

while ((leidos = read(sock_datos, buffer, sizeof(buffer))) > 0){
	printf("Soy el proceso padre (%d) antes del write\n", getpid());
	write(sock_datos, buffer, leidos);
	printf("Soy el proceso padre (%d) después del write\n", getpid());

}

close(sock_datos);

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

//Retorno del fork en el padre
else{
	printf("Soy el proceso padre (%d) antes de terminar\n", getpid());
	close(sock_datos);

}

}


}
