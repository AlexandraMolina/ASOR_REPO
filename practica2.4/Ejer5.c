#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>


int main(){
  
  char *tuberia="tuberia";
  char *tuberia2="tuberia2";
  char buffer[257];
  mkfifo(tuberia, 0644);
  mkfifo(tuberia2, 0644);

  int pipe1= open(tuberia,O_RDONLY | O_NONBLOCK);
  int pipe2= open(tuberia2,O_RDONLY | O_NONBLOCK);

  int change, current;

  while (change!=-1){
    fd_set c;
    FD_ZERO(&c);
    FD_SET(pipe1,&c);
    FD_SET(pipe2,&c);
    int num;

    change= select((pipe1<pipe2)? pipe2+1: pipe1+1,&c, NULL,NULL,NULL);

    if (change >0){
        if(FD_ISSET(pipe1,&c)){
            num=1;
            current=pipe1;
        }else if(FD_ISSET(pipe2,&c)){
            num=2;
            current=pipe2;
        }

        ssize_t tam=256;
        while(tam==256){
            tam= read(current, buffer, 256);
            buffer[tam]='\0';
            printf("Tuberia %i: %s", num,buffer);

        }

        if(tam !=256 && num ==1){
            close(pipe1);
            pipe1=open(tuberia,O_RDONLY | O_NONBLOCK);
            if(pipe1==-1){
                perror("Error al abrir la segunda tuberia");
                close(pipe1);
                close(pipe2);
                exit(EXIT_FAILURE);
            }

        }else if (tam !=256 && num==2)
        {
            close(pipe2);
            pipe2= open(tuberia2, O_RDONLY | O_NONBLOCK);
                if (pipe1==-1){
                    perror("Error al aprir la segunda tuberia");
                    close(pipe1);
                    close(pipe2);
                    exit(EXIT_FAILURE);
                }
        }
    }
  }
  close(pipe1);
  close(pipe2);
  return 0;  
}