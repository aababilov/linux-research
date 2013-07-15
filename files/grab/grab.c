#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>
#include <linux/input.h>
#include <string.h>

int
main()
{
	int i, fd;
	char fname[] = "/dev/input/event0"; 
	for (i = 0; i < 10; ++i) {
	    fname[sizeof(fname) - 2] = i + '0';
	    fd = open(fname, O_RDWR);
	    if (fd == -1) {
		if (errno == EACCES)
	    		printf("cannot open %s for r/w\n", fname);
		continue;
	    }	    
	    if (ioctl(fd, EVIOCGRAB, (void*)1) == 0)
		    printf("grabbed %s\n", fname);

	     else 
		printf("cannot grab %s: %s\n", fname, strerror(errno));

	}
	sleep(5);
	return 0;
}
