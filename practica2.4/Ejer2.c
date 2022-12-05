#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


#define PIPE_R 0
#define PIPE_W 1
#define BUF_SIZE 1024

int main(){
 
    int p_h[2];
    int h_p[2];
    char buff[BUF_SIZE+1];
    ssize_t tam=0;

    if(pipe(p_h)==-1){
        printf("Error en la creación de la tubería de padre a hijo\n");
        perror("pipe()");
        exit(EXIT_FAILURE);
    }

    if(pipe(h_p)==-1){
        printf("Error en la creación de la tubería hijo a padre\n");
        perror("pipe()");
        exit(EXIT_FAILURE);
    }

    pid_t pid=fork();

    switch (pid)
    {
    case -1:
        printf("Error invocando al fork\n");
        perror("fork()");
        exit(EXIT_FAILURE);
        break;
    case 0:

        if(close(p_h[PIPE_W])==-1){
            perror("close()");
            exit(EXIT_FAILURE);
        }

        if(close(h_p[PIPE_R])==-1){
            perror("close()");
            exit(EXIT_FAILURE);
        }

        int i=0;
        while (i < 10)
        {
            tam = read(p_h[PIPE_R], &buff, BUF_SIZE);

            if(tam == -1){
                
                printf("No se puede leer tubería de padre a hijo");
                perror("read()");
                exit(EXIT_FAILURE);
            }

            i++;

            printf("Recibido: %s\n", buff);

            sleep(1);

            if(write(h_p[PIPE_W],'l', 1)==-1){
                printf("Error al escribir en la tubería de hijo a padre\n");
                perror("write()");
                exit(EXIT_FAILURE);
            }
        }

        if (write(h_p[PIPE_W],'q',1)==-1){
            printf("Error al escribir a la tubería del hijo al padre");
            perror("write()");
            exit(EXIT_FAILURE);
        }
        close(p_h[PIPE_R]);
        close(h_p[PIPE_W]);
        break;

    default:

        if(close(h_p[PIPE_W])==-1){
            perror("close()");
            exit(EXIT_FAILURE);
        }

        if(close(p_h[PIPE_R])==-1){
            perror("close()");
            exit(EXIT_FAILURE);
        }

        char cb[1]={'l'};

        while (cb[0] != 'q')
        {
            tam = read(STDIN_FILENO, &buff, BUF_SIZE);

            if(tam == -1){
                printf("No se puede leer la entrada");
                perror("read()");
                exit(EXIT_FAILURE);
            }
            buff[tam-1]='\0';

            if(write(p_h[PIPE_W],buff,tam)==-1){
                printf("Error al escribir en la tubería de padre a hijo\n");
                perror("write()");
                exit(EXIT_FAILURE);
            }

            tam=read(h_p[PIPE_R],cb,1);
                if(tam == -1){
                printf("No se puede leer la tubería del hijo al padre");
                perror("read()");
                exit(EXIT_FAILURE);
            }

        }
        close(p_h[PIPE_W]);
        close(h_p[PIPE_R]);

        printf("Mensaje Recibido \n");
        break;
    }


    return 0;
}