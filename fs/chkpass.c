#include <stdio.h>
#include <stdlib.h>
#include <crypt.h>
#include <shadow.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char *passwd = NULL;
	struct spwd *shadow_line;
	char *crypted;

	if ( argc < 2 )
	{
		fprintf(stderr, "Usage...\n");
		exit(1);
	}

	passwd = getpass("PassWord: ");
	if ( passwd == NULL )
	{
		fprintf(stderr, "input Err\n");
		exit(1);
	}
	
	shadow_line = getspnam(argv[1]);
	if ( shadow_line == NULL )
	{
		perror("getspnam()");
		exit(1);
	}
	
	crypted = crypt(passwd, shadow_line->sp_pwdp);

	if ( strcmp(crypted, shadow_line->sp_pwdp) == 0 )
		puts("ok!");
	else
		puts("fail!");

	exit(0);
}
