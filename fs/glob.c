#include <stdio.h>
#include <stdlib.h>
#include <glob.h>
#include <unistd.h>
#include <string.h>

#define SIZE 1024

int main(int argc, char argv[])
{
	glob_t globres;
	int i, ret;
	char buf[SIZE];

	if ( getcwd(buf, SIZE) == NULL )
	{
		perror("getcwd()");
		exit(1);
	}

	strcat(buf, "/*");
	
	ret = glob(buf, 0, NULL, &globres);

	if ( ret )
	{
		printf("Error Code = %d\n", ret);
		exit(1);
	}
	
	for ( i = 0; i < globres.gl_pathc; i++)
		puts(globres.gl_pathv[i]);

	globfree(&globres);
	exit(0);
}
