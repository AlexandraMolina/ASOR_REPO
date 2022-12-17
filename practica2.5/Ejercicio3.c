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
#define BUFFER_SIZE 128

int main(int argc, char **argv){

 if (argc != 4){

        printf("Faltan argumentos\n", argv[0]);
    }
 struct addrinfo hints, *result;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;


    int info= getaddrinfo(argv[1], argv[2], &hints,&result);
    if (info != 0){
        printf("Error getaddrinfo(): %s\n", gai_strerror(info));
        exit(EXIT_FAILURE);
    }


    int socketUDP= socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    if (socketUDP == -1){
        perror("Error en [Socket()]");
        exit(EXIT_FAILURE);
    }

    if(bind(socketUDP, result->ai_addr, result->ai_addrlen)!=0){
        perror("Error en [bind()]");
        exit(EXIT_FAILURE);
    }
    freeaddrinfo(result);

   
    ssize_t envio= sendto(socketUDP, argv[3], 2, 0, result->ai_addr, result->ai_addrlen);

    if (envio==-1){
        perror("Error [sento()]");
        exit(EXIT_FAILURE);
    }

    if (argv[3][0]=='t' || argv[3][0]=='t'){
        struct sockaddr_storage client_addr;
        socklen_t client_addrlen = sizeof(client_addr);
        char buffer[BUFFER_SIZE+1];

        ssize_t bytes=recvfrom(socketUDP, buffer, BUFFER_SIZE, 0, (struct sockaddr *) &client_addr, &client_addrlen);
        if(bytes==-1){
            perror("Error [recvfrom()]");
            exit(EXIT_FAILURE);
        }

        buffer[bytes]='\0';
        printf("[Respuesta]: %s\n", buffer);
    }
    return 0;
}