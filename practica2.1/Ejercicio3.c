#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

const int MERROR=255;

int main(){
    char *err;
    for(int i=0; i<MERROR;i++){
        printf("ERROR(%d): %s\n",i,strerror(i));
    }
    return 1;
}