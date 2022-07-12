#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <glob.h>

#define SIZE 1024

static int errorGlob(const char *epath, int eerrno)
{
	puts(epath);
	fprintf(stderr, "error: %s\n", strerror(eerrno));
	return 1;
}


static int isCover(const char *path)
{
	char *str = strrchr(path, '/');
	if ( str == NULL )
		exit(1);
	if ( strcmp(str, "/.") == 0 || strcmp(str, "/..") == 0 )
		return 1;
	return 0;
}

static int64_t mydu(const char *path)
{
	int i;
	struct stat statres;
	char nextpath[SIZE];
	glob_t globres;
	int ret;
	int64_t sum = 0;

	ret = lstat(path, &statres);
	if ( ret != 0 )
	{
		perror("lstat()");
		exit(1);
	}
	if ( !S_ISDIR(statres.st_mode) )
		return statres.st_blocks;

	strncpy(nextpath, path, SIZE);
	strncat(nextpath, "/*", SIZE-1);
	ret = glob(nextpath, GLOB_ERR, errorGlob, &globres);
	if ( ret != 0 )
	{
		fprintf(stderr, "glob() -> 1: ERROR CODE = %d\n",ret);
		exit(1);
	}

	strncpy(nextpath, path, SIZE);
	strncat(nextpath, "/.*", SIZE-1);
	ret = glob(nextpath, GLOB_APPEND, NULL, &globres);
	if ( ret != 0 )
	{
		fprintf(stderr, "glob() -> 2: ERROR CODE = %d\n", ret);
		exit(1);
	}
	for ( i = 0; i < globres.gl_pathc; i++ )
	{
		if ( !isCover(globres.gl_pathv[i]) )
			sum += mydu(globres.gl_pathv[i]);
	}
	
	sum += statres.st_blocks;

	return sum;
}

int main(int argc, char *argv[])
{
	if ( argc < 2 )
	{
		fprintf(stderr, "Usage...\n");
		exit(1);
	}

	printf("%ld\n", mydu(argv[1])/2);
	// printf("is = %d\n", isCover(argv[1]));

	exit(0);
}
