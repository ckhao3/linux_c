#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define FILENAME "/tmp/out"
#define SIZE 1024

int main(int argc, char **argv)
{
	FILE *fp = NULL;
	time_t tme;
	struct tm *tm = NULL;
	int count = 0;
	fp = fopen(FILENAME, "a+");
	char buf[SIZE];
	if ( fp == NULL )
	{
		perror("foprn()\n");
		exit(1);
	}

	while ( fgets(buf, SIZE, fp) != NULL )
		count++;

	while( 1 )
	{
		tme = time(NULL);
		if ( tme == -1 )
		{
			fclose(fp);
			perror("time()\n");
			exit(1);
		}

		tm = localtime(&tme);
		if ( tm == NULL )
		{
			fclose(fp);
			fprintf(stderr, "localtime() ERROR\n");
			exit(1);
		}
		fprintf(fp, "%-4d%dh-%dm-%ds\n", ++count, tm->tm_hour, tm->tm_min, tm->tm_sec);

		fflush(fp);

		sleep(1);
	}


	fclose(fp);
	exit(0);
}
