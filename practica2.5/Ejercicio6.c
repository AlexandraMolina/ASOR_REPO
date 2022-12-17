#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

#define SOCKET_BACKLOG 5
#define BUFFER_LEN 128

int main(int argc, char *argv[])
{

	if (argc != 3)
	{
		printf("Falta Argumentos: \n", argv[0]);
		exit(EXIT_FAILURE);
	}

    struct addrinfo hints;
	struct addrinfo * result;
	
	memset(& hints, 0, sizeof(struct addrinfo));
	
	hints.ai_family 	= AF_UNSPEC;
	hints.ai_socktype 	= SOCK_STREAM;
	hints.ai_flags 		= AI_PASSIVE;

    int info = getaddrinfo(argv[1], argv[2], &hints, &result);
	if (info != 0)
	{
		printf("Error: getaddrinfo(): %s\n", gai_strerror(info));
		exit(EXIT_FAILURE);
	}

    int socketTCP = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (socketTCP == -1)
	{
		perror("Error: socket()\n");
		exit(EXIT_FAILURE);
	}
	
	
	int bindr = bind(socketTCP, result->ai_addr, result->ai_addrlen);
	if (bindr== -1)
	{
		perror("Error: bind()\n");
		exit(EXIT_FAILURE);
	}
	
	freeaddrinfo(result);

    int listenr = listen(socketTCP, SOCKET_BACKLOG);
	
	if (listenr == -1)
	{
		perror("Error: listen()\n");
		exit(EXIT_FAILURE);
	}

    struct sockaddr_storage client_addr;
	socklen_t client_addrlen = sizeof(client_addr);
	int client_sd;
    int infoClient;
	char client_host[NI_MAXHOST];
	char client_server[NI_MAXSERV];
	ssize_t recv_len;
	ssize_t send_len;
	char client_buffer[BUFFER_LEN + 1];


    while (1)
    {
        client_sd = accept(socketTCP, (struct sockaddr *) &client_addr, &client_addrlen);
        if (client_sd == -1)
		{
			perror("Error: accept()\n");
			exit(EXIT_FAILURE);
		}

        infoClient = getnameinfo((struct sockaddr *) &client_addr, client_addrlen, client_host, NI_MAXHOST, client_server, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
		if (infoClient != 0)
		{
			printf("Error: getnameinfo(): %s\n", gai_strerror(infoClient));
			exit(EXIT_FAILURE);
		}
		
		printf("Conexión desde %s:%s\n", client_host, client_server);

        while(1){
            recv_len = recv(client_sd, client_buffer, BUFFER_LEN, 0);
			if (recv_len == -1)
			{
				perror("Error: recv()\n");
				exit(EXIT_FAILURE);
			}
			else if (recv_len == 0)
			{
			 break;
			}
			
			send_len = send(client_sd, client_buffer, strlen(client_buffer), 0);
			if (send_len == -1)
			{
				perror("Error: send()\n");
				exit(EXIT_FAILURE);
			}
			
			memset(client_buffer, 0, BUFFER_LEN);
		}
		
		printf("Conexión terminada\n");
	}

	return 0;
    
}	
