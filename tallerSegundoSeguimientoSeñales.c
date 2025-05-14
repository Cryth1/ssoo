#include "signal.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


// JOSÉ RODRIGUEZ
// TOMÁS GUTIERRREZ
// CRISTIAN GUERRERO
void handler() {}

void print_debug_tree() {
  char cmd[50];
  sprintf(cmd, "pstree -lp %d", getpid());
  system(cmd);
}

int main(int argc, char *argv[]) {

  signal(SIGUSR1, handler);

  int cant_hijos = 5;
  int i;
  pid_t root = getpid();
  pid_t pid_hijos[cant_hijos];
  for (i = 0; i < cant_hijos; i++) {
    pid_hijos[i] = fork();
    if (!pid_hijos[i]) {
      break;
    }
  }

  if (getpid() == root) {
    usleep(40);
    print_debug_tree();
    usleep(10);
    printf("%d Padre: enviando señal a %d \n", getpid(),
           pid_hijos[cant_hijos - 1]);
    kill(pid_hijos[cant_hijos - 1], SIGUSR1);
    printf("Padre: Señal enviada a %d\n", pid_hijos[cant_hijos - 1]);
    pause();
    printf("Padre: Señal recibida del hijo %d\n", pid_hijos[0]);

    for (int j = 0; j < cant_hijos; j++) {
      wait(NULL);
    }

  } else {

    pid_t pid_hh = fork();
    if (pid_hh) {
      pause();
      printf("%d enviando señal a hijo de hijo %d\n", getpid(), pid_hh);
      kill(pid_hh, SIGUSR1);
      pause();
      if (i != 0) {
        printf("%d enviando señal a hermano a la izquierda %d\n", getpid(),
               pid_hijos[i - 1]);
        kill(pid_hijos[i - 1], SIGUSR1);
      } else {
        printf("%d enviando señal a padre raiz %d \n", getpid(), root);
        kill(root, SIGUSR1);
      }

    } else {
      pause();
      if (i == 2) {
        pid_t pid_hhh = fork();
        if (pid_hhh) {
          printf("%d enviando señal a bisnieto %d\n", getpid(), pid_hhh);
          kill(pid_hhh, SIGUSR1);
          pause();
          printf("%d enviando señal a padre de nieto %d\n", getpid(),
                 getppid());
          kill(getppid(), SIGUSR1);

        } else {
          printf("%d enviando señal a padre de bisnieto %d\n", getpid(),
                 getppid());
          kill(getppid(), SIGUSR1);
        }
      } else {
        printf("%d enviando señal a padre de nieto %d\n", getpid(), getppid());
        kill(getppid(), SIGUSR1);
      }
    }
  }

  return EXIT_SUCCESS;
}
