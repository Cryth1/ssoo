#include "stdlib.h"
#include <stddef.h>
#include "sys/shm.h"
#include <stdio.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <signal.h>

unsigned int sizeof_dm(int rows, int cols, size_t sizeElement) {
    size_t size;
    size = rows * sizeof(void *);         // Tamaño del índice de punteros
    size += (cols * rows * sizeElement);  // Tamaño de los datos
    return size;
}

void create_index(void **m, int rows, int cols, size_t sizeElement) {
    int i;
    size_t sizeRow = cols * sizeElement;  // Tamaño de una fila en bytes
    
    m[0] = (void *)((char *)m + rows * sizeof(void *));
    
    for (i = 1; i < rows; i++) {
        m[i] = (m[i-1] + sizeRow);
    }
}


int main(int argc, char *argv[])
{


  double **matrix = NULL;
  int rows = 10, cols = 10;
  size_t sizeMatrix = sizeof_dm(rows,  cols, sizeof(double));

  int shmid = shmget(IPC_PRIVATE, sizeMatrix, IPC_CREAT|0600);
  matrix = shmat(shmid, NULL, 0);
  create_index((void*) matrix, rows, cols, sizeof(double));

  if(fork()){
    for(int i = 0; i < rows; i++){
      for(int j = 0; j < cols; j++){
        matrix[i][j] = (i*cols) + j;
      }
    }
    signal
  }
  else{
    pause();
    for(int i = 0; i < rows; i++){
      for(int j = 0; j < cols; j++){
        printf("%f ", matrix[i][j]);
      }
      printf("\n");
    }
  }

  shmdt(matrix);
  shmctl(shmid, IPC_RMID, NULL);
  return EXIT_SUCCESS;
}
