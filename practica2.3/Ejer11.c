#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char *argv[]){

    if (argc!=2){
        printf("Introduzca los segundos\n", argv[0]);
        return -1;
    }

    sigset_t st;

    if(sigemptyset(&st)==-1){ perror("sigemptyset()"); }
    if(sigaddset(&st,SIGINT)==-1){perror("sigaddset()");}
    if(sigaddset(&st,SIGTSTP)==-1){perror("sigaddset()");}
    if(sigprocmask(SIG_BLOCK,&st,NULL)==-1){perror("sigprocmask()");}


    char *sleep_secs= getenv("SLEEP_SECS");
    if(sleep_secs==NULL){printf("No se ha encontrado la variable de entorno\n");exit(-1);}
    sleep(atoi(sleep_secs));

    sigset_t pending;
    sigemptyset(&pending);

    if (sigpending(&st)==-1){perror("sigpending()"); exit(-1);}
    
    if (sigismember(&pending,SIGINT)==1){
        printf("Se ha recibido la señal SIGINT");
        
    }
    if (sigismember(&pending,SIGTSTP)==1)
    {
        printf("Se ha recibido la seña SIGTSTP");
        if(sigdelset(&st,SIGINT)==-1){perror("sigdelset()");exit(-1); }
        if(sigprocmask(SIG_UNBLOCK,&st,NULL)==-1){perror("sigprocmask()");exit(-1);}

    }
    printf("Se ha desbloqueado la señal SIGTSTP\n");
    return 0;
    }