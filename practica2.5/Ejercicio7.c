#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#define BUFFER_SIZE 128
int main(int argc, char *argv[])
{

	if (argc != 3)
	{
		printf("Falta Argumentos: \n", argv[0]);
		exit(EXIT_FAILURE);
	}

    struct addrinfo hints;
	struct addrinfo * result;
	
	memset(&hints, 0, sizeof(struct addrinfo));
	
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
	
	
	int conex = connect(socketTCP, result->ai_addr, result->ai_addrlen);
	if (conex== -1)
	{
		perror("Error: connect()\n");
		exit(EXIT_FAILURE);
	}
	
	freeaddrinfo(result);

    

	char host[NI_MAXHOST];
	char server[NI_MAXSERV];
    ssize_t client;


    while (1)
    {
        char str[BUFFER_SIZE];
		fgets(str, BUFFER_SIZE, stdin);
		str[strlen(str)-1] = '\0';

        client=send(socketTCP,str,sizeof(str),0);
       if (client == -1)
		{
			perror("Error: sendto()\n");
			exit(EXIT_FAILURE);
		}

        if(strcmp(str,"q")!=0){

            char buffer[BUFFER_SIZE+1];

            ssize_t recv_result = recv(socketTCP, buffer, BUFFER_SIZE, 0);
			if (recv_result == -1)
			{
				perror("Error: recvfrom()\n");
				exit(EXIT_FAILURE);
			}
			
			buffer[recv_result] = '\0';
			
			printf("Respuesta: %s\n", buffer);
        }else{
            close(socketTCP);
			exit(EXIT_SUCCESS);
        }
	}

	return 0;
    
}	
