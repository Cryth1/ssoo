#include "stdlib.h" #include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  FILE *archivo;
  archivo = fopen("test1.txt", "r");

  if (archivo == NULL) {
    return EXIT_FAILURE;
  }
  
  int *vector = malloc(5000000 * sizeof(int))
  return EXIT_SUCCESS;
}
