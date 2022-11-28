#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile int stop=0;

static void handler(int sen){
    if (sen==SIGUSR1){stop=1;}
}

int main(int argc, char *argv[]){

       if (argc!=2){
        printf("Introduzca los segundos\n"), argv[0];
        return -1;
    }

    sigset_t mask;

    if(sigemptyset(&mask)==-1){perror("sigemptyset()");}
    if(sigaddset(&mask,SIGUSR1)==-1){perror("sigaddset()");}
    if(sigprocmask(SIG_UNBLOCK,&mask,NULL)==-1){perror("sigprocmask()");}


    struct sigaction sa;
    sa.sa_handler=handler;

    if(sigaction(SIGUSR1,&sa,NULL)==-1){perror("sigaction()");}
    int i=0;
    int sec= atoi(argv[1]);

    while (i<sec && !stop)
    {
        sleep(i);
        i++;
    }

    if(stop){printf("Saliendo\n");}
    else{printf("Borrando ejecutable\n");
        if(unlink(argv[0])==-1){perror("unlink()");}}

    return 0;
    
}
