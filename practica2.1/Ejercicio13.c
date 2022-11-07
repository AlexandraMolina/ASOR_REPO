#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

int main(){
  struct timeval tv;
  int rc = gettimeofday(&tv, NULL);
  int start = tv.tv_usec;
  int i;
  for (i = 0; i < 10000; i++);
  int rc2 = gettimeofday(&tv, NULL);
  int end = tv.tv_usec;

  printf("Ha tardado (ms): %i\n", end - start);

  return 1;
}




