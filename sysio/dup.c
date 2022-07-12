#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FILENAME "/tmp/out"

int main()
{
	int fd;
	fd = open(FILENAME, O_WRONLY|O_CREAT|O_TRUNC, 0600);
	if ( fd < 0 )
	{
		perror("open()");
		exit(1);
	}

	int fd2 = dup2(fd, 1);
	if ( fd != 1 )
		close(fd);

	puts("hello!");
	printf("fd1 = %d\n", fd);
	printf("fd2 = %d\n", fd2);
	
	exit(0);
}
