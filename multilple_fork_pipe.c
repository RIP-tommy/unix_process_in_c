#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

void cal_sum(int start, int end, int *arr, int *ret)
{
	int sum = 0;
	int i;
	for (i = start; i < end; i++)
		sum += arr[i];
	*ret = sum;
}

int main(int argc, char *argv[])
{
	int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
	int arr_size = sizeof(arr) / sizeof(int);
	int id1 = fork();
	int id2 = fork();
	int fd[2];
	if (id1 == -1 || id2 == -1)
		return 1;
	if (pipe(fd) == -1)
		return 2;
	int sum;
	if (id1 == 0)
	{
		if (id2 == 0)
		{
			cal_sum(0, arr_size / 4, arr, &sum);
			printf("Sum from process y: %d\n", sum);
			close(fd[0]);
			if (write(fd[1], &sum, sizeof(int)) == -1)
				return 3;
			close(fd[1]);
		}
		else
		{
			cal_sum(arr_size / 4, arr_size / 2, arr, &sum);
			printf("Sum from process x: %d\n", sum);
			close(fd[0]);
			if (write(fd[1], &sum, sizeof(int)) == -1)
				return 4;
			close(fd[1]);
		}
	}
	else
	{
		if (id2 == 0)
		{
			cal_sum(arr_size / 2, (arr_size * 3) / 4, arr, &sum);
			printf("Sum from process z: %d\n", sum);
			close(fd[0]);
			if (write(fd[1], &sum, sizeof(int)) == -1)
				return 5;
			close(fd[1]);
		}
		else
		{
			cal_sum((arr_size * 3) / 4, arr_size, arr, &sum);
			printf("Sum from parent process: %d\n", sum);
			int total;
			int sum_from_child;
			while (wait(NULL) != -1 || errno != ECHILD)
			{
				printf("Waited for a child to finish\n");
				close(fd[1]);
				if (read(fd[0], &sum_from_child, sizeof(int)) == -1)
					return 6;
				total = sum + sum_from_child;
			}
			printf("Total sum is %d\n", total);
		}
	}
	return 0;
}
