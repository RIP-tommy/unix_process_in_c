#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int fd[2];
	if (pipe(fd) == -1)
	{
		return 1;
	}

	int pid = fork();
	if (pid < -1)
		return 2;
	if (pid == 0)
	{
		// Child process 1: Execute 1st command.
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execlp("ping", "ping", "-c", "5", "google.com", NULL);
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		execlp("grep", "grep", "rtt ", NULL);
		close(fd[0]);
		wait(NULL);
	}
	return 0;
}
