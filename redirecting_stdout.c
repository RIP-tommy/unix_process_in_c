#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int ac, char *av[])
{
	int pid = fork();
	if (pid == -1)
		return 1;
	if (pid == 0)
	{
		// Child Process
		int file = open("ping_result.txt", O_WRONLY | O_CREAT, 0777);
		if (file == -1)
		{
			printf("Error occured when excuting a file open function.");
			return 2;
		}
		printf("The fd to the ping_result: %d\n", file);
		dup2(file, STDOUT_FILENO);
		close(file);

		int errcode = execlp("ping", "ping", "-c", "1", "google.com", NULL);
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
