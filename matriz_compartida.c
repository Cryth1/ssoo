
#include "stdlib.h"
#include <stddef.h>
#include "sys/shm.h"
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
unsigned int sizeof_dm(int rows, int cols, size_t sizeElement) {
    size_t size;
    size = rows * sizeof(void *);         // Tamaño del índice de punteros
    size += (cols * rows * sizeElement);  // Tamaño de los datos
    return size;
}

void create_index(void **m, int rows, int cols, size_t sizeElement) {
    int i;
    size_t sizeRow = cols * sizeElement;  // Tamaño de una fila en bytes
    
    //m[0] = (void *)((char *)m + rows * sizeof(void *));
    m[0] = m + rows; 
    for (i = 1; i < rows; i++) {
        m[i] = (m[i-1] + sizeRow);
    }
}

void handler() {}


int main(int argc, char *argv[])
{


  double **matrix = NULL;
  signal(SIGUSR1, handler);
  int rows = 10, cols = 10;
  size_t sizeMatrix = sizeof_dm(rows,  cols, sizeof(double));

  int shmid = shmget(IPC_PRIVATE, sizeMatrix, IPC_CREAT|0600);
  matrix = shmat(shmid, NULL, 0);
  create_index((void*) matrix, rows, cols, sizeof(double));
  
  pid_t h = fork();
  if(h){
    usleep(40);
    for(int i = 0; i < rows; i++){
      for(int j = 0; j < cols; j++){
        matrix[i][j] = (i*cols) + j;
      }
    }
    kill(h, SIGUSR1);
    wait(NULL);
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
