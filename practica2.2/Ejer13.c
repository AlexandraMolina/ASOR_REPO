#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/*ls > dirlist 2>&1 salida estandar y la salida de de errores se van a ver en dirlist
ls 2>&1 > dirlist los errores se ven por pantallas y la salida estandar en el fichero dirlist
*/


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
    dup2(dfile,STDERR_FILENO);
    perror("Error");
    close(dfile);

    return 1;


}
