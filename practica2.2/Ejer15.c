#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

int main(int argc, char **argv){
    int status;
    char buffer[1024];
        if (argc < 2){
        printf("Especificar ruta del archivo\n");
        return -1;
    }

     int dfile =open(argv[1], O_CREAT | O_RDWR, 00777);
    
    if(dfile==-1){
        printf("Error en el archivo\n");
        return -1;
    } 

    struct flock lock;

    status = fcntl(dfile, F_GETLK,&lock);

    if(status==-1){
        perror("error con fcntl\n");
        return -1;
    }

    if(lock.l_type==F_UNLCK){

        lock.l_type=F_WRLCK;
        lock.l_whence=SEEK_SET;
        lock.l_start=0;
        lock.l_len=0;
        lock.l_pid=0;

        status=fcntl(dfile,F_SETLK,&clock);
         if(status==-1){
            perror("error con fcntl\n");
            close(dfile);
            return -1;
         }

         printf("Cerrojado fijado\n");

         time_t tiempo= time(NULL);
         struct tm *tm;
         tm = localtime(&tiempo);
         strftime(buffer,sizeof(buffer),"%d/%m,/%Y %H:%M:%S", tm);
        
        printf("Fecha y hora: %s\n",buffer);
        write(dfile,&buffer,strlen(buffer));
        sleep(30);

        lock.l_type=F_UNLCK;

        status=fcntl(dfile,F_SETLKW,&lock);

            if(status==-1){
            perror("error con fcntl\n");
            close(dfile);
            return -1;
         }else{
            printf("Cerrojo libre");
         }


    }else{
        printf("cerrojo bloqueado\n");
        close(dfile);
        return -1;
    }
    close(dfile);
    return 0;

}