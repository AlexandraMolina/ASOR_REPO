#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    if (argc<2){
        printf("Error, introduzca comando\n", argv[0]);
        return -1;

    }

    int tamaño=0;

    for (int i = 0; i < argc; i++)
    {
        tamaño +=strlen(argv[i]);
    }

    char cmd[tamaño];
    sprintf(cmd, "%s", argv[1]);

    for (int  i = 2; i < argc; i++)
    {
        sprintf(cmd,"%s %s", cmd,argv[1]);
    }

    if (system(cmd)==-1)
    {
        perror("system()");
        return -1;
    }

    printf("El comando terminó de ejecutarse\n");

    return 0;   
    
}