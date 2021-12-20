#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int ac, char *av[])
{
	int fd1[2]; // C -> P
	int fd2[2]; // P -> C
	if (pipe(fd1) == -1)
		return 1;
	if (pipe(fd2) == -1)
		return 1;
	int id = fork();
	if (id == -1)
		return 2;
	if (id == 0)
	{
		close(fd1[0]);
		close(fd2[1]);
		int x;
		if (read(fd2[0], &x, sizeof(x)) == -1)
			return 2;
		close(fd2[0]);
		printf("A Child process received %d\n", x);
		x *= 4;
		if (write(fd1[1], &x, sizeof(x)) == -1)
			return 2;
		close(fd1[1]);
	}
	else
	{
		close(fd1[1]);
		close(fd2[0]);
		int y = rand() % 10;
		printf("y is %d\n", y);
		if (write(fd2[1], &y, sizeof(y)) == -1)
			return 2;
		close(fd2[1]);
		if (read(fd1[0], &y, sizeof(y)) == -1)
			return 2;
		close(fd1[0]);
		printf("y multiply 4 is %d\n", y);
		wait(NULL);
	}
	return 0;
}
