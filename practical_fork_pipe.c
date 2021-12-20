#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	int arr[] = {1, 2, 3, 11, 12, 13};
	int arr_size = sizeof(arr) / sizeof(int);
	int start, end;
	int fd[2];
	if (pipe(fd) == -1)
	{
		return 1;
	}

	int id = fork();
	if (id == -1)
	{
		return 2;
	}

	if (id == 0)
	{
		start = 0;
		end = arr_size / 2;
	}
	else
	{
		start = arr_size / 2;
		end = arr_size;
	}

	int sum = 0;
	int i;
	for (i = start; i < end; i++)
	{
		sum += arr[i];
	}
	if (id == 0)
	{
		close(fd[0]);
		if (write(fd[1], &sum, sizeof(sum)) == -1)
		{
			return 3;
		}
		close(fd[1]);
		printf("Sum from a child process is %d\n", sum);
	}
	else
	{
		int sum_from_child;
		close(fd[1]);
		if (read(fd[0], &sum_from_child, sizeof(sum_from_child)) == -1)
		{
			return 4;
		}
		close(fd[0]);
		printf("Sum from a parent process is %d\n", sum);
		int total = sum + sum_from_child;
		printf("Total sum is %d\n", total);
		wait(NULL);
	}
	return 0;
}
