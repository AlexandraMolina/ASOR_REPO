#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/sysmacros.h>
#include <time.h>
 /*st_mtime es la última modificación dentro del archivo
   st_ctime: Es la última modificación de permisos, archivo, de nombre, etc*/
   
int main(int argc, char **argv){
    
    if (argc < 2){
        printf("Especificar ruta del archivo\n");
        return -1;
    }

    struct stat buffer;
    int statInt= stat(argv[1],&buffer);

    if(statInt==-1){
        printf("No existe el directorio");
        return -1;
    }

    printf("Major: %d\n", major(buffer.st_dev));
    printf("Minor: %d\n", minor(buffer.st_dev));
    printf("Número de inodo: %li\n",buffer.st_ino);
    printf("Tipo de fichero: %li\n",buffer.st_mode);

    mode_t mode= buffer.st_mode;
    if(S_ISLNK(mode)){
        
        printf("%s enlace simbólico\n", argv[1]);

    }else if(S_ISREG(mode)){
       
        printf("%s Fichero ordinario\n",argv[1]);

    }else if(S_ISDIR(mode)){
        
        printf("%s Directorio\n",argv[1]);

    }

    time_t t= buffer.st_atime;
    struct tm *tiempo=localtime(&t);

    printf("La hora en la que se accedió el fichero por última vez: %d:%d\n",tiempo->tm_hour,tiempo->tm_min);

}
