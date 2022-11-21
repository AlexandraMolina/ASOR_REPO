#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char **argv){

      if (argc < 2){
        printf("Especificar ruta del archivo\n");
        return -1;
    }

    DIR *dir = opendir(argv[1]);

    if(dir==NULL){
        printf("No existe el directorio\n");
        return -1;
    }

    struct dirent *current;
    struct stat info;
    off_t total_tam=0;

    while((current= readdir(dir))!=NULL){
        size_t tam=sizeof(char)*(tam+strlen(current->d_name)+3);
        char *path= (char *) malloc(tam);
        sprintf(path,"%s/%s", argv[1],current->d_name);
        

        if(stat(path,&info)==-1){
            perror("Error obteniendo la información de la entrada del directorio");
            closedir(dir);
            return -1;
        }

        if(current->d_type==DT_LNK){
            long path_max= pathconf("/",_PC_NAME_MAX);
            char * lName= (char *) malloc(path_max+1);
            readlink(path,lName,path_max+1);

            printf("Enlace: %s -> %s\n", current->d_name,lName);
        }else if(current->d_type==DT_REG){

            printf("Fichero regular: %s",current->d_name);

            if((info.st_mode & (S_IXUSR | S_IXGRP, S_IXOTH))>0){
                printf("*");
            }

            total_tam+=info.st_size;
            printf("(%ld bytes)\n", info.st_size);

        }else if(current->d_type==DT_DIR){
            printf("Directorio: %s\n", current->d_name);
        }
        free(path);

        closedir(dir);

        float total_kb= total_tam/1000;
        printf("Tamaño de ficheros regulares: %.2f KB\n", total_kb);

        return 0;

    }



}
