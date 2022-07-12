#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include "proto.h"

int main(int argc, char **argv)
{
	if ( argc < 2 )
	{
		fprintf(stderr, "Usage: <IP>\n");
		exit(1);
	}

	int sd;
	struct msg_st msg;
	struct sockaddr_in raddr;

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if ( sd < 0 )
	{
		perror("socket()");
		exit(1);
	}

	// bind();

	strcpy(msg.name, "World");
	msg.math = htonl(70);
	msg.chinese = htonl(80);

	raddr.sin_family = AF_INET;
	raddr.sin_port = htons(atoi(RCVPORT));
	inet_pton(AF_INET, argv[1], (void *)&raddr.sin_addr);
	
	if ( sendto(sd, &msg, sizeof(msg), 0, (void *)&raddr, sizeof(raddr)) < 0 )
	{
		perror("sendto()");
		exit(1);
	}

	puts("OK");
	
	close(sd);

	exit(0);
}
