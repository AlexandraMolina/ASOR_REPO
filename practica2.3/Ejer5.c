#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sched.h>
#include <sys/resource.h>

int main(){

    struct rlimit rlimite;
    if(getrlimit(RLIMIT_NOFILE,&rlimite)==-1){
        perror("No se pudieron obtener los datos");
        return -1;
    }

    printf("PID: %i\n", getpid());
    printf("PPID: %i\n", getppid());
    printf("PGID: %i\n", getpgid(getpid()));
    printf("SSID: %d\n", getsid(getpid()));
    printf("Maximo de ficheros: %d\n", rlimite.rlim_cur);
    printf("Directorio actual: %s\n",getcwd(NULL,getpid()));

    return 0;
}