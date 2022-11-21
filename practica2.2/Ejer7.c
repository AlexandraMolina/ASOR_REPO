#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>


int main(){
    
    const mode_t mask= S_IWGRP | S_IXOTH;
    const char PATH[]="ej7.txt";
    umask(mask);
    int dfile = open(PATH, O_CREAT | O_RDONLY, 0777);
    if(dfile==-1){
        perror("Error en la apertura del archivo");
    }else{
        close(dfile);
        printf("Descriptor = %i\n", dfile);
    }


    return 0;
}