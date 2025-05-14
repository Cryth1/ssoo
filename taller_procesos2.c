#include "stdio.h"
#include "unistd.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int nivel = 0;

  if(argc > 1) {
    nivel = atoi(argv[1]);
  }
  pid_t root = getpid();

  for (int i = 0; i < 2; i++) {
    pid_t señal = fork();
    if(señal == 0){
      if(nivel == 0){
        execl("./taller_procesos2_cuadrado.c", "cuadrado" , NULL);
      }
      else {
        execl("./taller_procesos2_triangulo.c", "triangulo", NULL); }
    }
    exit(1);
  }

  return 0;
}
