#include <stdio.h>
#include <stdlib.h>

int main(){
	FILE *fp = NULL;
	long count = 2L*1024L*1024L*1024L;
	fp = fopen("tmp","w");
	if (fp == NULL) {
		perror("fopen()");
		exit(1);
	}
	while (count-- > 0) {
		fputc(0, fp);
	}
	fclose(fp);

	exit(0);
}
