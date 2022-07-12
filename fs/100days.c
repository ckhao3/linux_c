#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1024

int main(int argc, char **argv)
{

	time_t stamp;
	struct tm *tm = NULL;
	char buf[SIZE];
	time_t ret;

	time(&stamp);
	if ( stamp == (time_t)-1 )
	{
		perror("time()");
		exit(1);
	}

	tm = localtime(&stamp);
	strftime(buf, SIZE, "Now:%Y-%m-%d", tm);
	puts(buf);

	tm->tm_mday += 100;
	ret =  mktime(tm);
	if ( ret == -1)
	{
		fprintf(stderr, "mktime() ERROR");
		exit(1);
	}
	strftime(buf, SIZE, "Now:%Y-%m-%d %h(%P)", tm);
	puts(buf);

	exit(0);
}
