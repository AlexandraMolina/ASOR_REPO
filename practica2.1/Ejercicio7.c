#include <unistd.h>
#include <stdio.h>

int main(){

    const char *path = "/home/umaru/Documentos/ASOR/Práctica 2.1";
    printf("Longitud máxima de enlaces: %ld\n", pathconf(path,_PC_LINK_MAX));
    printf("Número máximo de una ruta: %ld\n", pathconf(path,_PC_PATH_MAX));
    printf("Número máximo de un nombre de fichero: %ld\n", pathconf(path,_PC_NAME_MAX));
    return 0;
}
