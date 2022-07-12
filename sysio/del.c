#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdint.h>

#define BUFSIZE 1024
#define DEBUG() printf("-------------");fflush(NULL)

int main(int argc, char *argv[])
{
	if ( argc < 2 )
	{
		fprintf(stderr, "Usage error ...\n");
		exit(1);
	}
	int rfd, wfd;
	int count = 0;
	uint32_t i, j;

	char buf[BUFSIZE];
	ssize_t len, ret;

	rfd = open(argv[1], O_RDONLY);
	wfd = open(argv[1], O_RDWR);

	while ( (len = read(rfd, buf, BUFSIZE)) > 0 )
	{
		i = 0;
		while ( 1 )
		{
			if ( buf[i++] == '\n' )
				count++;
			if ( i > len )
				break;
		}
	}
	printf("count = %d\n", count);

	close(wfd);
	close(rfd);

	exit(0);
}
