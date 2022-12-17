#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#define BUFFER_SIZE 2
#define MESSAGE_SIZE 128

void gestionarMensajes(int socketd);

int main(int argc, char **argv)
{

	if (argc != 3)
	{
		printf("Faltan Argumentos\n", argv[0]);
		
		exit(EXIT_FAILURE);
	}


	struct addrinfo hints;
	struct addrinfo *result;


	memset(&hints, 0, sizeof(struct addrinfo));
	
	hints.ai_family 	= AF_UNSPEC;
	hints.ai_socktype 	= SOCK_DGRAM;
	hints.ai_flags 		= AI_PASSIVE;

	int info = getaddrinfo(argv[1], argv[2], &hints, &result);
	
	if (info != 0)
	{
		printf("Error getaddrinfo(): %s\n", gai_strerror(info));
		
		exit(EXIT_FAILURE);
	}
	
	
	int socketUDP = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (socketUDP == -1)
	{
		printf("Error: no pudo abrirse el socket (socket()).\n");

		exit(EXIT_FAILURE);
	}
	

	if (bind(socketUDP, result->ai_addr, result->ai_addrlen) == -1)
	{
		printf("Error: no pudo asociarse el socket a la dirección (bind()).\n");

		exit(EXIT_FAILURE);
	}
	
	freeaddrinfo(result);

	
	for (int i = 0; i < 5; i++)
	{
		pid_t pid = fork();

		switch(pid)
		{
			case -1:
				return 1;
			case 0:
				gestionarMensajes(socketUDP);
				return 0;
			default:
				break;
		}
	}

	for (int i = 0; i < 5; i++)
	{
		int hijo = wait(NULL);

		printf("Terminado Hijo %d\n", hijo);
	}
	
	exit(EXIT_SUCCESS);
}

void gestionarMensajes(int socketd)
{
	struct sockaddr_storage client_addr;
	socklen_t client_addrlen = sizeof(client_addr);
	

	char host[NI_MAXHOST];
	char server[NI_MAXSERV];
	char buffer[BUFFER_SIZE + 1];
	time_t tiempo;
	size_t time_bytes;
	struct tm *tm;
	char msg[MESSAGE_SIZE + 1];
	

	while (1)
	{
		ssize_t bytes = recvfrom(socketd, buffer, BUFFER_SIZE, 0, (struct sockaddr *) &client_addr, &client_addrlen);
		buffer[bytes - 1] = '\0';
		
		getnameinfo((struct sockaddr *) &client_addr, client_addrlen, host, NI_MAXHOST, server, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
		printf("Recibidos %ld bytes desde host %s y servicio %s: %s\n", bytes, host, server, buffer);
		

		tiempo = time(NULL);
		tm = localtime(&tiempo);
		
		if (buffer[0] == 't')
		{
			time_bytes = strftime(msg, MESSAGE_SIZE, "%T", tm);
			msg[time_bytes] = '\n';
			msg[time_bytes + 1] = '\0';
			
			if (sendto(socketd, msg, time_bytes + 2, 0, (struct sockaddr *) &client_addr, client_addrlen) == -1)
			{
				printf("sendto()\n");
				exit(EXIT_FAILURE);
			}
		}
		else if (buffer[0] == 'd')
		{
			time_bytes = strftime(msg, MESSAGE_SIZE, "%F", tm);
			msg[time_bytes] = '\n';
			msg[time_bytes + 1] = '\0';
			
			if (sendto(socketd, msg, time_bytes + 2, 0, (struct sockaddr *) &client_addr, client_addrlen) == -1)
			{
				perror("Error: endto()\n");
				exit(EXIT_FAILURE);
			}
		}
		else if (buffer[0] == 'q')
		{
			printf("Saliendo...\n");
			
			exit(EXIT_SUCCESS);
		}
		else
		{
			printf("Comando no soportado: %s\n", buffer);
		}
	}
}