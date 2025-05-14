#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
void *oldhandler;
void sighandler(int sig) {}
int main(int argc, char *argv[]) {
  oldhandler = signal(SIGUSR1, sighandler);
  if (oldhandler == SIG_ERR) {
    perror("signal:");
    exit(EXIT_FAILURE);
  }

  pid_t root = getpid();
  pid_t *hijos;
  pid_t pidhijo;
  int i;

  char position[3];

  
  for (i = 0; i < 2; i++) {
    pidhijo = fork();
    if (pidhijo) {
      break;
    }
   snprintf(position, sizeof(position), "h%d", i+1); 
  }
  // hijos = calloc(5, sizeof(pid_t));
  pid_t pidhijos2[2];

  if (i == 2) {
    for (int j = 0; i < 2; i++) {
      pidhijos2[i] = fork();
      if (pidhijos2[i] == -1) {
        perror("fork:");
        exit(EXIT_FAILURE);
      }
      if (pidhijos2[i] == 0) {
        break;
      }
    }
  }


  if(getpid() == root){

    printf("p");
    usleep(100);
    kill(pidhijo, SIGUSR1);
    pause();
  }
  else if (i == 2) {

  
  }
  else {
  
  }
  
  return EXIT_SUCCESS;
}
