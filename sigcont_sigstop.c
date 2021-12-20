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
	{
		while (1)
		{
			printf("Some output\n");
			usleep(50000);
		}
	}
	else
	{
		kill(pid, SIGSTOP);

		int t;
		do
		{
			printf("Time in seconds for excution: ");
			scanf("%d", &t);

			if (t > 0)
			{
				kill(pid, SIGCONT);
				sleep(t);
				kill(pid, SIGSTOP);
			}
		} while (t > 0);
		kill(pid, SIGKILL);
		wait(NULL);
	}
	return 0;
}
