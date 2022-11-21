#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv){

      if (argc < 2){
        printf("Especificar ruta del archivo\n");
        return -1;
    }

    struct stat buffer;
    int statInt= stat(argv[1],&buffer);
    
    if (statInt==-1){
        printf("No Se ha encontrado\n");
        return -1;
    }

    char* hard= malloc(sizeof(char)*(5+strlen(argv[1])));
    char* sym = malloc(sizeof(char)*(5+strlen(argv[1])));

    strcpy(hard,argv[1]);
    strcpy(sym, argv[1]);

    hard= strcat(hard,".hard");
    sym = strcat(sym,".sym");


    if(S_ISREG(buffer.st_mode)){
        

        if(symlink(argv[1],sym)==-1){
            printf("No se ha creado el enlace simbolico\n");
        }else{
            printf("Se ha creado el enlace simbolico\n");
        }

        if(link(argv[1],hard)==-1){
            printf("No se ha creado el enlace duro\n");
        }else {
            printf("Se ha creado el enlace duro\n");
        }
    }else{
        printf("No es un fichero\n");
    }
       return 0;
}