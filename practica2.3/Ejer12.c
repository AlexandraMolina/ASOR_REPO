#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile int contador_Sint=0, contador_stspt=0;

static void handler(int sen){

    switch (sen)
    {
    case SIGINT:
        contador_Sint++;
        break;
    
    case SIGTSTP:
        contador_stspt++;
        break;
    }
}

int main(){
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags= SA_RESTART;
    sa.sa_handler= handler;

    if(sigaction(SIGINT,&sa,NULL)==-1){perror("sigaction()");exit(-1);}
    if(sigaction(SIGTSTP,&sa,NULL)==-1){perror("sigaction()");exit(-1);}

    sigset_t st;
    if(sigfillset(&st)==-1){perror("sigfillset()");}
    if(sigdelset(&st,SIGINT)==-1){perror("sigdelset()");}
    if(sigdelset(&st,SIGTSTP)==-1){perror("sigdelset()");}


    while(contador_Sint+contador_stspt <10){sigsuspend(&st);}

    printf("SIGINT: %d\n",contador_Sint);
    printf("SIGTSTP: %d\n", contador_stspt);
    
    return 0;
}

