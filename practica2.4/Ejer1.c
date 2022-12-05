#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char **argv){

    if (argc != 2 ){
        printf("Faltan argumentos\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int fd[2];
    pid_t pid;

    if(pipe(fd)==-1){
        printf("Error invocando pipe \n");
        perror("pipe()");
        exit(EXIT_FAILURE);

    }

    pid=fork();

    switch (pid)
    {
    case -1:
        printf("Error invocando el fork \n");
        perror("fork()");
        exit(EXIT_FAILURE);
        break;
    case 0:
        close(fd[0]);
        dup2(fd[1],STDOUT_FILENO);
        close(fd[1]);
        execlp(argv[1],argv[1],argv[2], NULL);
        break;
    default:
        close(fd[1]);
        dup2(fd[0],STDIN_FILENO);
        close(fd[0]);
        execlp(argv[3],argv[3],argv[4],NULL);
        break;
    }

    return 0;
}
