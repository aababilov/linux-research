#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char**argv, char**env){
  int nf;
  char buf[128];
  printf("args: %s; %s\n", argv[0], argv[1]);
  nf = atoi(argv[1]);
  lseek(nf, 0, SEEK_SET);
  buf[read(nf, buf, sizeof buf)] = '\0';
  printf("%s\n", buf);
  close(nf);
  return 0;
}
