#include <stdio.h>
#include <stdlib.h>
#include "unistd.h"

int main(int argc, char *argv[])
{ 
  pid_t root = getpid();
  int n = 4;
  int i;

  for (i = 0; i < n; i++) {
    if(!fork()){
      break;
    }
    
  }

  if((i+1)%2 == 0){
    for(int j = 0; j < i;j++){
      if(!fork()){
        break;
      }
    }
  }
  else {
    char i_str[10];
    sprintf(i_str, "%d", i,NULL); 
    execl("./cuadrado_tallerprocesos3.c", "cuadrado", i_str, NULL);
  }
  return EXIT_SUCCESS;
}
