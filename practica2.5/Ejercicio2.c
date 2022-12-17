#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <time.h>
#define BUFFER_SIZE 2
#define MESSAGE_SIZE 128

int main(int argc, char *argv[]){

    if (argc != 3){

        printf("Faltan argumentos\n", argv[0]);
        exit(EXIT_FAILURE);
    }


    struct addrinfo hints, *result;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_protocol 	= 0;
	hints.ai_canonname 	= NULL;
	hints.ai_addr 		= NULL;
	hints.ai_next 		= NULL;


    int info= getaddrinfo(argv[1], argv[2], &hints,&result);
    if (info != 0){
        printf("Error getaddrinfo(): %s\n", gai_strerror(info));
        exit(EXIT_FAILURE);
    }


    int socketUDP= socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    if (socketUDP == -1){
        printf("Error en [Socket()]\n");
        exit(EXIT_FAILURE);
    }

    if(bind(socketUDP, result->ai_addr, result->ai_addrlen)==-1){
        printf("Error en [bind()]\n");
        exit(EXIT_FAILURE);
    }
    freeaddrinfo(result);

    char buf[BUFFER_SIZE+1];
    char host[NI_MAXHOST];
    char server[NI_MAXSERV];

    struct sockaddr_storage client_addr;
    socklen_t client_addrlen= sizeof(client_addr);
 

    while(1){

        ssize_t bytes = recvfrom(socketUDP, buf, BUFFER_SIZE,0,(struct sockaddr *) &client_addr, &client_addrlen);
        buf[bytes-1]='\0';

        getnameinfo((struct sockaddr *)&client_addr, client_addrlen, host,NI_MAXHOST,server, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);
        printf("Recibidos %i byte de %s:%s\n",bytes,host,server);

        time_t tiempo=time(NULL);
        struct tm *tm =localtime(&tiempo);
        char msg[MESSAGE_SIZE+1];

        if (buf[0]=='t'){
            size_t tiempoBytes= strftime(msg, MESSAGE_SIZE, "%I:%M:%S %p", tm);
            msg[tiempoBytes]='\n';
            msg[tiempoBytes+1] ='\0';

            if(sendto(socketUDP, msg, tiempoBytes+2,0, (struct sockaddr *)&client_addr,client_addrlen)==-1){
                printf("Error [sento()]\n");
                exit(EXIT_FAILURE);
            }
        }else if(buf[0]=='d'){
            size_t tiempoBytes= strftime(msg, MESSAGE_SIZE, "%Y-%m-%d", tm);
            msg[tiempoBytes]='\n';
            msg[tiempoBytes+1] ='\0';
            if(sendto(socketUDP, msg, tiempoBytes+2,0, (struct sockaddr *)&client_addr,client_addrlen)==-1){
                printf("Error [sento()]\n");
                exit(EXIT_FAILURE);
            }

        }else if(buf[0]=='q'){
            printf("Saliendo...\n");
            exit(EXIT_SUCCESS);
        }else{
            printf("Comando no soportado: %s\n", buf[0]);
        }
    }
    return 0;
}