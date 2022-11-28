#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sched.h>
#include <sys/resource.h>

int main(){
    char *nombre_politica;
    struct sched_param sp;
    int politica, min, max;

    sched_getparam(0,&sp);

    politica= sched_getscheduler(getpid());
    min= sched_get_priority_min(politica);
    max= sched_get_priority_max(politica);
    
    switch (politica)
    {
    case SCHED_OTHER:
            nombre_politica="OTHER";
        break;
    case SCHED_FIFO:
            nombre_politica="FIFO";
        break;
    case SCHED_RR:
            nombre_politica="RR";
        break;    
    default:
            nombre_politica="Desconocido";
        break;
    }
    
    printf("Politica de planificación: %s\n",nombre_politica);
    printf("Prioridad proceso actual: %d\n", sp.sched_priority);
    printf("Prioridad máxima: %d\n", max);
    printf("Prioridad minima: %d\n", min);


    return 0;
    }