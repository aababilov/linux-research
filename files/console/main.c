#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/vt.h>

#include "getfd.h"


int main()
{
	struct vt_stat vtstat;
	int consfd = getfd(NULL);
	if (ioctl(consfd, VT_GETSTATE, &vtstat)) {
            perror("VT_GETSTATE");
            return 8;
	}
	printf("active terminal %d\n", vtstat.v_active);
	return 0;
}
