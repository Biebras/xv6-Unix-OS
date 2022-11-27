#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  int p[2]; //file descriptors for pipe
  char readBuff[4];
  
  //Creating pip
  pipe(p);

  if(fork() == 0)//child
  {
    read(p[0], readBuff, 4);
    close(p[0]);
    printf("%d: received %s\n", getpid(), readBuff);

    write(p[1], "pong", 4);
    close(p[0]);
  }
  else //parent
  {
    write(p[1], "ping", 4);
    close(p[1]);

    read(p[0], readBuff, 4);
    close(p[0]);
    printf("%d: received %s\n", getpid(), readBuff);
  }

  exit(0);
}
