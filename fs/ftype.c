#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static void ftype(char *mode, const char *fname)
{
	struct stat statres;
	if ( stat(fname, &statres) < 0 )
	{
		perror("stat()");
		exit(1);
	}

	// file type
	switch (statres.st_mode & 0170000)
	{
		case (0140000) : mode[0] = 's'; break;
		case (0120000) : mode[0] = 'l'; break;
		case (0100000) : mode[0] = '-'; break;
		case (0060000) : mode[0] = 'b'; break;
		case (0040000) : mode[0] = 'd'; break;
		case (0020000) : mode[0] = 'c'; break;
		case (0010000) : mode[0] = 'p'; break;
		default: mode[0] = '?';
	}

	// owner permission
	if ( statres.st_mode & (1 << 8) ) mode[1] = 'r';
	if ( statres.st_mode & (1 << 7) ) mode[2] = 'w';
	if ( statres.st_mode & (1 << 6) ) mode[3] = 'x';

	// group permission
	if ( statres.st_mode & (1 << 5) ) mode[4] = 'r';
	if ( statres.st_mode & (1 << 4) ) mode[5] = 'w';
	if ( statres.st_mode & (1 << 3) ) mode[6] = 'x';

	// others permission
	if ( statres.st_mode & (1 << 2) ) mode[7] = 'r';
	if ( statres.st_mode & (1 << 1) ) mode[8] = 'w';
	if ( statres.st_mode & (1 << 0) ) mode[9] = 'x';

}

int main(int argc, char *argv[])
{
	if ( argc < 2 )
	{
		fprintf(stderr, "Usage...\n");
		exit(1);
	}

	char mode[11] = "----------";
	
	ftype(mode, argv[1]);
	
	puts(mode);

	exit(0);
}
