#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netdb.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <sys/select.h>
#define BUFFER_SIZE 2
#define MESSAGE_SIZE 128

int main(int argc, char **argv)
{

	if (argc != 3)
	{
		printf("Falta argumentos\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	struct addrinfo hints;
	struct addrinfo *result;

	memset(&hints, 0, sizeof(struct addrinfo));
	
	hints.ai_family 	= AF_UNSPEC;
	hints.ai_socktype 	= SOCK_DGRAM;
	hints.ai_flags 		= AI_PASSIVE;

    int info= getaddrinfo(argv[1], argv[2], &hints,&result);
    if (info != 0){
        printf("Error getaddrinfo(): %s\n", gai_strerror(info));
        exit(EXIT_FAILURE);
    }

    int socketUDP = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

     if (socketUDP == -1){
        printf("Error en [Socket()]\n");
        exit(EXIT_FAILURE);
    }

    if(bind(socketUDP, result->ai_addr, result->ai_addrlen)!=0){
        printf("Error en [bind()]\n");
        exit(EXIT_FAILURE);
    }
    freeaddrinfo(result);

  struct sockaddr_storage client_addr;
	socklen_t client_addrlen = sizeof(client_addr);
	char host[NI_MAXHOST];
	char server[NI_MAXSERV];
	char buffer[BUFFER_SIZE + 1];
  char msg[MESSAGE_SIZE + 1];

    fd_set setdf;
    int df=-1;

    while(1){
        FD_ZERO(&setdf);
        FD_SET(0,&setdf);
        FD_SET(socketUDP,&setdf);
        df= select(socketUDP+1, &setdf, NULL, NULL, NULL);
        if (df==-1){
            perror("Error [select()]");
            exit(EXIT_FAILURE);
        }

        time_t tiempo= time(NULL);
        struct tm *tm = localtime(&tiempo);
        
        if (FD_ISSET(0,&setdf)){
              int b = read(0, buffer,BUFFER_SIZE);
              printf("Recibidos %d bytes\n", b);
        }else{

           ssize_t bytes = recvfrom(socketUDP, buffer, BUFFER_SIZE, 0, (struct sockaddr *) &client_addr, &client_addrlen);
            getnameinfo((struct sockaddr *) &client_addr, client_addrlen, host, NI_MAXHOST, server, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);
            printf("[Recibidos] %i byte(s) de %s:%s\n", bytes, host, server);
            buffer[bytes-1] = '\0';
        }
       

        if (buffer[0] == 't'){
        size_t tiempoBytes = strftime(msg, MESSAGE_SIZE,"%I:%M:%S %p", tm);
        msg[tiempoBytes]='\n';
        msg[tiempoBytes+1] = '\0';


        if(FD_ISSET(0,&setdf)){
          printf("%s\n", msg);

        }else{
          if (sendto(socketUDP, msg, tiempoBytes + 2, 0, (struct sockaddr *) &client_addr, client_addrlen) == -1)
				  {
					perror(" Error [sendto()]\n");
					exit(EXIT_FAILURE);
				  }
        }
       

      }else if (buffer[0] =='d'){
        size_t tiempoBytes = strftime(msg, MESSAGE_SIZE, "%Y-%m-%d", tm);
        msg[tiempoBytes] = '\n';
        msg[tiempoBytes+1] = '\0';
          if(FD_ISSET(0,&setdf)){
          printf("%s\n", msg);

            }else{
                if (sendto(socketUDP, msg, tiempoBytes + 2, 0, (struct sockaddr *) &client_addr, client_addrlen) == -1)
      				    {
			      		  perror(" Error [sendto()]\n");
					        exit(EXIT_FAILURE);
				         }
            }

      }else if (buffer[0] =='q'){
        printf("Saliendo...\n");
        exit(EXIT_SUCCESS);
      }else{
        printf("Comando no soportado: %d...\n", buffer[0]);
      }
    }

      return 0;

        }
