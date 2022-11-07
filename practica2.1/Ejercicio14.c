#include <time.h>
#include <stdio.h>
#include <sys/time.h>

int main(){
    time_t t=time(NULL);
    struct tm *info =localtime(&t);
    printf("Año actual: %i\n", 1900+info->tm_year);
    return 1;
}