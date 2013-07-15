#include <unistd.h>
#include <stdio.h>

int main()
{
	int i, pgrp, child;	
	if ((child = fork()) != 0) {
		printf("parent process; pid: %d grp: %d\n",
		       getpid(), getpgrp());
		fflush(stdout);
		waitpid(child, 0, 0);
		return 0;
	}
	FILE *f = fopen("log", "w+t");
	fprintf(f, "pid: %d grp: %d\n", getpid(), getpgrp());	
	pgrp = setpgrp();
	fprintf(f, "successfull: %d grp: %d\n", pgrp, getpgrp());
	for (i = 0; i < 3; ++i)
		fprintf(f, "%s\n", ttyname(i));
	return 0;
}
