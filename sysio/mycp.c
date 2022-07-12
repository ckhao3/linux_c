#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#define BUFSIZE 1024

int main(int argc, char *argv[])
{
	if ( argc < 3 )
	{
		fprintf(stderr, "Usage ...\n");	
		exit(EXIT_FAILURE);
	}
	int sfd, dfd;
	char buf[BUFSIZE];
	ssize_t len, ret, pos;
	sfd = open(argv[1],O_RDONLY);
	if ( sfd < 0 )
	{
		perror("open()");
		exit(EXIT_FAILURE);
	}
	dfd = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0600);
	if ( dfd < 0 )
	{
		close(sfd);
		perror("open()");
		exit(EXIT_FAILURE);
	}


	while(1)
	{
		len = read(sfd, buf, BUFSIZE);	
		if ( len < 0 )
		{
			perror("read()");
			break;
		}
		if ( len == 0)
			break;
		pos = 0;
		while ( len > 0 )
		{
			ret = write(dfd, buf+pos, len);
			if ( ret < 0 )
			{
				close(sfd);
				close(dfd);
				perror("write()");
				exit(EXIT_FAILURE);
			}
			pos += ret;
			len -= ret;
		}
	}

	close(sfd);
	close(dfd);
	exit(EXIT_SUCCESS);
}
