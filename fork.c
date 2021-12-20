#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int id = fork();
	if (id != 0) // to fork only from master process b.c every child process id is 0
	{
		fork();
	}
	printf("Hello world\n");
	// if (id == 0) {
	// 	printf("Hello from child process\n");
	// } else {
	// 	printf("Hello from the main process\n");
	// }
	return 0;
}
