#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sched.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
   
   if (argc<2){
        printf("Error, introduzca comando\n", argv[0]);
        return -1;

    }

    pid_t pid=fork();

    switch (pid)
    {
    case -1:
        perror("fork()");
        exit(EXIT_FAILURE);
        break;
    case 0:
        pid_t Nsession= setsid();
        printf("Proceso [Hijo] con PID %d y PPID %d\n", getpid(),getppid());
        int fd= open("/tmp/daemon.out", O_CREAT | O_RDWR, 00777);
        if(fd<0){
            perror("open()");
            exit(-1);
        }
        int fde= open("/tmp/daemon.err", O_CREAT | O_RDWR, 00777);
        if(fde<0){
            perror("open()");
            exit(-1);
        }
    
        break;

        int null= open("dev/null", O_CREAT | O_RDWR, 00777);
          if(null<0){
            perror("open()");
            exit(-1);
        }
        int fd1=dup2(fd,2);
        int fd2=dup2(fde,1);
        int fd3=dup2(null,0);

        if (execvp(argv[1],argv+1)==-1){
            printf("NO se ha ejecutado con exito");
            exit(-1);

        }
    
    default:
    printf("Proceso [Padre] con PID %d\n", getpid());
        break;
    }

    return 0;
}