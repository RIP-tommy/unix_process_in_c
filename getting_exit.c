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
		int errcode = execlp("pingc", "ping", "-c", "1", "google.com", NULL);
		if (errcode == -1)
		{
			printf("Error occured when excuting program.\n");
			return 2;
		}
	}
	else
	{
		int w_status;
		// Parent process
		wait(&w_status);
		if (WIFEXITED(w_status))
		{
			int status_code = WEXITSTATUS(w_status);
			if (status_code == 0)
			{
				printf("Sucess!\n");
			}
			else
			{
				printf("Failure with status code %d\n", status_code);
			}
		}
		printf("Some post processing goes here!\n");
	}
	return 0;
}
