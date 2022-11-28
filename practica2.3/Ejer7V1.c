#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*La cadena de se debe mostrar solo se ejecuta cuando se usa system porque en exec 
sustituye la imagen del programa  a la imagen que se ha pasado por argumentos 

la diferenica entre ps -el y "ps -el" cuando se pasa por parametros ps -el significa dos argumentos
si se quiere ejecutar como system es necesario unirlos, mientras que con las "" es un string que permite ejecutar
directamente el comando system sin unirlos.
*/
int main(int argc, char *argv[]){
    if (argc<2){
        printf("Error, introduzca comando\n", argv[0]);
        return -1;

    }

    pid_t pid = fork();
    switch (pid)
    {
    case -1:
        printf("No se ha creado proceso hijo");
        break;
    case 0:
        if(execvp(argv[1],argv+1)==-1){
            printf("No puede ejecutar comando");
        }
        break;
    
    default:
        printf("El comando terminó en ejecutarse");
        break;
    }

    return 0;

}