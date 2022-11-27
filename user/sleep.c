#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  //If no argument tell them how to use
  if(argc == 1)
  {
    printf("Usage: %s ticks\n", argv[0]);
    exit(1);
  }

  //There should always be only 2 arguments
  if(argc != 2)
  {
    printf("Bard argument count\n");
    exit(1);
  }

  //Number of ticks
  int ticks = atoi(argv[1]);

  //Call system call
  sleep(ticks);

  //if there was no error return 0
  exit(0);
}
