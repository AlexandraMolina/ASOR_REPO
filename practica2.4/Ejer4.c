#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv){

    if(argc !=2 ){
        printf("Falta argumentos\n", argv[0]);
        exit(EXIT_FAILURE);
    }    

    char *HOME = getenv("HOME");
    char *tuberia = strcat(HOME, "/tuberia");

    printf("PATH: %s\n", tuberia);
    mkfifo(tuberia, 0777);

    int fd= open(tuberia, O_WRONLY);
    write(fd,argv[1], strlen(argv[1]));
    close(fd);

    return 0;
}