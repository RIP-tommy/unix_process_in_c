#include <stdio.h>
#include <unistd.h>

#include <fcntl.h>

int main(int argc, char *argv[])
{
	int arr[] = {1, 2, 3, 4, 5, 6};
	int fd = open("sum", O_WRONLY);
	if (fd == -1)
	{
		printf("Failed to open a fifo file\n");
		return 1;
	}
	printf("Success opening a fifo file\n");
	if (write(fd, arr, sizeof(arr)) == -1)
		return 2;
	printf("Sucess writing a arr\n");
	close(fd);
	printf("Sucess closing a fifo file\n");
	fd = open("sum", O_RDONLY);
	if (fd == -1)
	{
		printf("Failed to open a fifo file\n");
		return 3;
	}
	int sum;
	if (read(fd, &sum, sizeof(int)) == -1)
	{
		printf("Failed to read a sum\n");
		return 4;
	}
	close(fd);
	printf("Sum is %d\n", sum);
	return 0;
}
