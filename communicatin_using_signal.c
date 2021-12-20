#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/wait.h>

void handle_sigusr1(int sig)
{
	printf("\n(HINT) Remember that multiplication is repetitive addition!\n");
}

int main(int argc, char *argv[])
{
	int pid = fork();
	if (pid == -1)
		return 1;
	if (pid == 0)
	{
		sleep(5);
		kill(getppid(), SIGUSR1);
	}
	else
	{
		struct sigaction sa = {0};
		sa.sa_flags = SA_RESTART;
		sa.sa_handler = &handle_sigusr1;
		sigaction(SIGUSR1, &sa, NULL);

		// Parent process
		int x;
		printf("What is the result of 3 X 5: ");
		scanf("%d", &x);
		if (x == 15)
			printf("Correct!\n");
		else
			printf("Wrong!\n");
	}
	return 0;
}
