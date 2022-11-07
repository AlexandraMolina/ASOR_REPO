#include <time.h>
#include <stdio.h>
#include <locale.h>

int main(){
    char str[128];
    const size_t max=100;
    const int BYear =1900;
    const char *formato ="%A, %d de %B de %Y, %H:%M";
    setlocale(LC_ALL, "es_ES");


    time_t t=time(NULL);
    struct tm *info =localtime(&t);
    size_t l= strftime(str,max,formato,info);

    printf("Hora: %s\n", str);
    return 0;
}