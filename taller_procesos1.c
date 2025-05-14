#include "stdio.h"
#include "unistd.h"
#include <stdlib.h>
#include "wait.h"

void print_process_tree(pid_t root)
{
  if(getpid()== root){
    char buff[50];
    sprintf(buff, "pstree -plA %d", root);
    usleep(10000);
    system(buff);
  }
}

int main(int argc, char *argv[])
{
  
  pid_t h, root = getpid();
  int i;

 for (i = 0; i < 4; i++) {
        if (!fork()) {
            break;
        }
    }

    
    if (i == 1) {
        if (!fork()) {
            fork(); 
            pause(); 
        } else {
           
            wait(NULL);
        }
    }

    if (i == 3) {
        if (!fork()) {
            fork(); 
            pause(); 
        } else {
            wait(NULL);
        }

    }
  print_process_tree(root);

  return 0;
}
