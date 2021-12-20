#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int fd[2];
	if (pipe(fd) == -1)
		return 1;

	int pid = fork();
	if (pid == -1)
		return 2;

	if (pid == 0)
	{
		// Child process
		close(fd[0]);
		char str[200];
		printf("Input string: ");
		fgets(str, 200, stdin);
		int str_len = strlen(str);
		str[str_len - 1] = '\0';
		if (write(fd[1], &str_len, sizeof(int)) < 0)
			return 3;
		if (write(fd[1], str, str_len) < 0)
			return 3;
		close(fd[1]);
	}
	else
	{
		// Parent process
		close(fd[1]);
		char str[200];
		int n, i;
		if (read(fd[0], &n, sizeof(int)) < 0)
			return 4;
		if (read(fd[0], str, n) < 0)
			return 4;
		close(fd[0]);
		printf("%s\n", str);
		wait(NULL);
	}

	return 0;
}
