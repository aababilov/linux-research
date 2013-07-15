#include <stdio.h>
#include <unistd.h>

int main()
{
	printf("Hello, ");
	fork();
	printf("world!\n");
	return 0;
}
