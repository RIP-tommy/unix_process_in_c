#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	if (mkfifo("myfifo1", 0777) == -1)
	{
		if (errno != EEXIST)
		{
			printf("Could not create a fifo file.");
			return 1;
		}
	}
	int fd = open("myfifo1", O_WRONLY);
	if (fd == -1)
		return 2;
	int a = 97;
	if (write(fd, &a, sizeof(a)) == -1)
		return 3;
	close(fd);
	return 0;
}
