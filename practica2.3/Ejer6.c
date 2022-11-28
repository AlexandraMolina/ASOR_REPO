#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sched.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

/*Si el padre termina antes que el hijo, el hijo se queda huerfano y 
el ppid lo recof la shell o init, en caso que el hijo termine antes que el padre
el proceso se queda como <defunct>*/
void imprimirAtributos(char *tipo){


  struct rlimit rlimite;
    if(getrlimit(RLIMIT_NOFILE,&rlimite)==-1){
        perror("No se pudieron obtener los datos");
        exit(EXIT_FAILURE);
    }

    printf("[%s]PID: %i\n",tipo, getpid());
    printf("[%s]PPID: %i\n",tipo, getppid());
    printf("[%s]PGID: %i\n",tipo, getpgid(getpid()));
    printf("[%s]SSID: %d\n",tipo, getsid(getpid()));
    printf("[%s]Maximo de ficheros: %d\n",tipo, rlimite.rlim_cur);
    printf("[%s]Directorio actual: %s\n",tipo,getcwd(NULL,getpid()));

}

int main(){
    pid_t pid= fork();

    switch (pid)
    {
    case -1:
        perror("Error Fork");
        exit(-1);
        break;
    case 0:
        printf("\n Proceso [Hijo] con PID %d y PPID %d\n", getpid(),getppid());
        if(chdir("/tmp")==-1){
            perror("Error chdir()");
            exit(EXIT_FAILURE);
        }

        imprimirAtributos("Hijo");
        
        break;

    default:
        printf("Proceso [Padre] con PID %d\n",getpid());
        imprimirAtributos("Padre");
        waitpid(pid,NULL,0);
        break;
    }

    return 0;
}