#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include "proto.h"

int main(int argc, char **argv)
{
	if ( argc < 3 )
	{
		fprintf(stderr, "Usage: <IP> <NAME>\n");
		exit(1);
	}

	if ( strlen(argv[2]) > NAMEMAX )
	{
		fprintf(stderr, "Name is too long\n");
		exit(1);
	}

	int sd;
	struct msg_st *msgp;
	struct sockaddr_in raddr;
	int msg_size;

	msg_size = sizeof(struct msg_st)+strlen(argv[2]);

	msgp = malloc(msg_size);
	if ( msgp == NULL )
	{
		perror("malloc()");
		exit(1);
	}

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if ( sd < 0 )
	{
		perror("socket()");
		exit(1);
	}

	// bind();

	strcpy(msgp->name, argv[2]);
	msgp->math = htonl(70);
	msgp->chinese = htonl(80);

	raddr.sin_family = AF_INET;
	raddr.sin_port = htons(atoi(RCVPORT));
	inet_pton(AF_INET, argv[1], (void *)&raddr.sin_addr);
	
	if ( sendto(sd, (void*)msgp, msg_size, 0, (void *)&raddr, sizeof(raddr)) < 0 )
	{
		perror("sendto()");
		exit(1);
	}

	puts("OK");
	
	close(sd);

	exit(0);
}
