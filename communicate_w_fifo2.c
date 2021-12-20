#include <stdio.h>
#include <unistd.h>

#include <fcntl.h>

int main(int argc, char *argv[])
{
	int arr[6];
	int fd = open("sum", O_RDONLY);
	if (fd == -1)
	{
		printf("Failed to open a fifo file\n");
		return 1;
	}
	printf("Success opening a fifo file\n");
	if (read(fd, arr, sizeof(int) * 6) == -1)
	{
		printf("Failed to a read fd\n");
		return 2;
	}
	printf("Sucess reading a arr\n");
	close(fd);
	printf("Sucess closing a fifo file\n");
	int sum = 0;
	for (int i = 0; i < 6; i++)
		sum += arr[i];
	fd = open("sum", O_WRONLY);
	if (fd == -1)
	{
		printf("Failed to open a fifo file\n");
		return 3;
	}
	if (write(fd, &sum, sizeof(int)) == -1)
	{
		printf("Faile to write a sum in a fifo file");
		return 4;
	}
	printf("Sucess writing a sum\n");
	close(fd);
	printf("Sucess closing a fifo file\n");
	return 0;
}
