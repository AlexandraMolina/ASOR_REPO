#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

int main(int argc, char *argv[]){

    if (argc !=2 ){
        printf("Faltan argumentos\n",argv[0]);
        exit (EXIT_FAILURE);
    }

    struct addrinfo hints, *result, *iter;

    memset(&hints,0, sizeof(struct addrinfo));

    hints.ai_family= AF_UNSPEC;
    hints.ai_socktype= 0;
    hints.ai_flags= AI_PASSIVE;
    hints. ai_protocol=0;
    hints.ai_canonname = NULL;
    hints.ai_addr=NULL;
    hints.ai_next=NULL;

    int info= getaddrinfo(argv[1], NULL, &hints,&result);
    if (info != 0){
        printf("Error getaddrinfo(): %s\n", gai_strerror(info));
        exit(EXIT_FAILURE);
    }

    for(iter=result; iter != NULL; iter= iter->ai_next){

        switch (iter->ai_family)
        {
        case AF_INET:;
            struct sockaddr_in *data = iter->ai_addr;
            char ip[INET_ADDRSTRLEN + 1 ]="";
            inet_ntop(AF_INET, &(data->sin_addr), ip, INET_ADDRSTRLEN+1);
            printf("%s\t", ip);
            break;
        case AF_INET6:;
            struct sockaddr_in6 *data1= iter->ai_addr;
            char ipv6[INET6_ADDRSTRLEN+1]="";
            inet_ntop(AF_INET6, &(data1->sin6_addr), ipv6, INET6_ADDRSTRLEN+1);
            printf("%s\t", ipv6);
            break;
        default:
            printf("Error: ai_family no definido");
            break;
        }
        printf("%i\t%i\t\n",iter->ai_family, iter-> ai_socktype);
    }

    freeaddrinfo(result);
    
    return 0;
}
