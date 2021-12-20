#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>

int main(int argc, char const *argv[])
{
	int pid = fork();
	if (pid == -1)
	{
		printf("Error Occured when forking a process");
		return 1;
	}
	if (pid == 0)
		while (1)
		{
			printf("Some output\n");
			usleep(50000);
		}
	else
	{
		sleep(1);
		kill(pid, SIGKILL);
		printf("Success kill a child process!\n");
		wait(NULL);
	}
	return 0;
}
