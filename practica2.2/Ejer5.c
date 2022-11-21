#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>


int main(){
    const char PATH[]="ej5.txt";
    int dfile = open(PATH, O_CREAT, 0645);

    if(dfile==-1){
        perror("Error en la apertura del archivo");
    }else{
        close(dfile);
        printf("Descriptor =%i\n", dfile);
    }


    return 0;
}