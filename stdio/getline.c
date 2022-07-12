#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		fprintf(stderr, "Usage ...\n");
		exit(EXIT_FAILURE);

	}
	char *buf = NULL;
	size_t n = 0;	
	FILE *fp = NULL;
	fp = fopen(argv[1], "r");
	if(fp == NULL)
	{
		perror("fopen()");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		if (getline(&buf, &n, fp) < 0)
			break;
		printf("%d\n", strlen(buf));
		printf("%d\n", n);
	}

	free(buf);
	fclose(fp);
	exit(EXIT_SUCCESS);
}
