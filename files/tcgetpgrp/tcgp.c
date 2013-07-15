#include <unistd.h>
#include <stdio.h>
#include <string.h>

const char *pname(int pid)
{
     static char buf[1024 * 8], fname[4+10+3+4];
     snprintf(fname, sizeof(fname), "/proc/%d/exe", pid);
     ssize_t l = readlink(fname, buf, sizeof(buf));
     if (l == -1)
          strcpy(buf, "cannot read link");
     else
          buf[l < sizeof(buf) ? l : sizeof(buf) - 1] = '\0';
     return buf;
}

int main()
{
     int pg = tcgetpgrp(0);
     printf("pg: %d (%s)\n", pg, pname(pg));
     int sid = getsid(0);
     printf("sid: %d (%s)\n", sid, pname(sid));
     int pgid = getpgid(0);
     printf("pgid: %d (%s)\n", pgid, pname(pgid));
     return 0;
}
