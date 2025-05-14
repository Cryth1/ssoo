#include <unistd.h>
#include "pthread.h"
#include <stdio.h>
#include <stdlib.h>

void* leer_adn(void* arg);

void error(char *msg){
  perror(msg);
  exit(-1);
}

int contA, contB, contC, contD = 0;
int 
 char *vector = NULL;

int main(int argc, char *argv[])
{
  int nucleos = 10;
  pthread_t tid[nucleos];
 
  FILE *archivo;
  archivo = fopen("./adn1_100.txt", "r");
  if(!archivo){
    error("archivo fopen");
  }

  int cant_bases;
  fscanf(archivo, "%d", &cant_bases);

  vector = calloc(cant_bases, sizeof(int));

  int c;

  for(int i = 0; i < cant_bases; i++){
    if((c= fgetc(archivo) != EOF)){
      char caracter = (char)c;
      vector[i] = caracter;
    }
  }
  return EXIT_SUCCESS;
}

void* leer_adn(void* arg){
  int* cantidad = (int *) arg;
  char* vectorBusqueda[7];
  int j = 0;
  for(int i = 0; i < *cantidad; i++){
    vectorBusqueda[j] = &vector[*cantidad + i];
    if(j = 6){
      vectorBusqueda[6] = "\0";
      if(strcomp)
    }
    j++
  }
}


