#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
    fork();
  }

  print_process_tree(root);

  return 0;
}
