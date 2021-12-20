#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	int id1 = fork();
	int id2 = fork();
	if (id1 == 0)
	{
		if (id2 == 0)
			printf("We are process y, id1: %d\n", id1);
		else
			printf("We are process x, id1: %d, id2: %d\n", id1, id2);
	}
	else
	{
		if (id2 == 0)
			printf("We are procces z, id1: %d\n", id1);
		else
			printf("We are the parent Process!, id1: %d, id2: %d\n", id1, id2);
	}
	while (wait(NULL) != -1 || errno != ECHILD)
		printf("Waited for a child to finish\n");
	return 0;
}
