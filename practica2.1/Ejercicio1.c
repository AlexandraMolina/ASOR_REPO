#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int main(){
    char *err;
    if (setuid(0)==-1){
        perror(err);
    }
    return 1;

}
