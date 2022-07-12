#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define FILENAME "/tmp/out"

int main()
{
	int fd;
	fd = open(FILENAME, O_RDWR);
	if ( fd < 0 )
	{
		perror("open()");
		exit(1);
	}
	
	int ret = ftruncate(fd, 2);
	if ( ret == -1 )
	{
		close(fd);
		perror("ftruncate()");
		exit(1);
	}
	
	close(fd);
	exit(0);
}
