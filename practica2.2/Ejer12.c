#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv){

        if (argc < 2){
        printf("Especificar ruta del archivo\n");
        return -1;
    }

    int dfile =open(argv[1], O_CREAT | O_RDWR, 00777);
    
    if(dfile==-1){
        printf("Error en el archivo\n");
        return -1;
    } 

    dup2(dfile,STDOUT_FILENO);
    printf ("Esto es una prueba de redirección\n", argv[1]);
    close(dfile);
    return 1;


}