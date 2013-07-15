#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(int argc, char**argv, char**env){
  int nf = open("j.t", O_RDWR|O_CREAT|O_TRUNC, 0644);
  int fdes[2];
  pipe(fdes);
  if (fork() == 0) {
    char buf[128], *args[3] = {"./chi", buf, 0};
    close(fdes[0]);
    sprintf(buf, "%d", fdes
    execve("chi", args, env);
  }
  
  
  return 0;
}
