#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int ac, char *av[])
{
	int pid = fork();
	if (pid == -1)
		return 1;
	if (pid == 0)
	{
		// Child Process
		execlp("ping", "ping", "-c", "3", "google.com", NULL);
	}
	else
	{
		// Parent process
		wait(NULL);
		printf("Success!\n");
		printf("Some post processing goes here!\n");
	}
	return 0;
}
