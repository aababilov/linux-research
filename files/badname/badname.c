#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	int i = open("./f\nret.txt", O_CREAT|O_WRONLY, 0644);
	close(i);
	return 0;
}
