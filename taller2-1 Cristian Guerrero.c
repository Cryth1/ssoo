#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <unistdio.h>
#include <wait.h>

void error(char *msg) {
  perror(msg);
  exit(-1);
}
int leerNumeros(char *filename, int **vec) {
  int c, numero, totalNumeros;
  FILE *infile;
  infile = fopen(filename, "r");
  if (!infile) {
    error("Error fopen\n");
  }
  fscanf(infile, "%d", &totalNumeros);
  *vec = (int *)calloc(totalNumeros, sizeof(int));
  if (!*vec) {
    error("error calloc");
  }
  for (c = 0; c < totalNumeros; c++) {
    fscanf(infile, "%d", &numero);
    (*vec)[c] = numero;
    printf("%d\n", numero);
  }
  fclose(infile);
  return c;
}

int main(int argc, char *argv[]) {
  remove("./out.txt");

  pid_t root = getpid();
  int cant_procesos = 10;
  int *vector = NULL;

  int cant_numeros = leerNumeros("./test2.in", &vector);
  int i;

  for (i = 0; i < cant_procesos; i++) {
    if (!fork()) {
      break;
    }
  }

  FILE *salida;
  salida = fopen("./out.txt", "a");
  if (!salida)
    error("error calloc");
  if (getpid() != root) {
    long int delta = cant_numeros / cant_procesos;
    long int inicio = delta * i;
    long int fin = inicio + delta;
    long int suma = 0;
    for (int j = inicio; j < fin; j++) {
      suma += vector[j];
    }

    fprintf(salida, "%ld\n", suma);
    fclose(salida);
    return EXIT_SUCCESS;
  }

  for (int k = 0; k < cant_procesos; k++) {
    wait(NULL);
  }

  FILE *resultado;
  resultado = fopen("./out.txt", "r");
  if (!resultado)
    error("error calloc");
  long int num2;
  long int sumaresultado = 0;
  while (fscanf(resultado, "%ld", &num2) == 1) {
    sumaresultado += num2;
  }
  printf("Cantidad de numeros: %d \n", cant_numeros);
  printf("Resultado de suma: %ld", sumaresultado);

  free(vector);
  // fclose(archivo);
  fclose(salida);
  fclose(resultado);
  return EXIT_SUCCESS;
}
