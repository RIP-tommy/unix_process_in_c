#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	// Creating a pipe
	int fd[2];
	if (pipe(fd) == -1)
		return 1;

	// Forking a process
	int pid = fork();
	if (pid == -1)
		return 1;

	if (pid == 0)
	{
		// Child process
		close(fd[0]);
		int arr[10];
		srand(time(NULL));
		int n = rand() % 10 + 1;
		printf("Sended n: %d\n", n);
		printf("Generated : ");
		for (int i = 0; i < n; i++)
		{
			arr[i] = rand() % 10;
			printf("%d ", arr[i]);
		}
		printf("\n");
		if (write(fd[1], &n, sizeof(int)) < 0)
			return 2;
		if (write(fd[1], arr, sizeof(int) * n) < 0)
			return 2;
		close(fd[1]);
	}
	else
	{
		// Parent process
		close(fd[1]);
		int arr[10];
		int n, sum = 0;
		if (read(fd[0], &n, sizeof(int)) < 0)
			return 2;
		printf("Received n: %d\n", n);
		if (read(fd[0], arr, sizeof(int) * n) < 0)
			return 2;
		close(fd[0]);
		printf("Received arr : ");
		for (int i = 0; i < n; i++)
		{
			sum += arr[i];
			printf("%d ", arr[i]);
		}
		printf("\n");
		printf("Sum is %d\n", sum);
		wait(NULL);
	}
	return 0;
}
