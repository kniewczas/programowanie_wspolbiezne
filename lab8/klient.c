#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include "data.h"

int main()
{
	int sd, size, bits;
	int num = 0;
   	struct sockaddr_in to;
	sd =  socket(PF_INET, SOCK_DGRAM, 0);

	//config of input address data
	memset(&to, 0x00, size);
	to.sin_family=AF_INET;
	to.sin_port = htons((ushort)PORT);
	inet_pton(PF_INET, IP_ADD, &to.sin_addr);
	size = sizeof(struct sockaddr_in);

	bind(sd,(struct sockaddr*) &to, size);

	printf("Enter the number pleasE!!:\n");
	scanf("%d", &num);

	num = htonl(num);
	sendto(sd,(char *) &num, sizeof(int), 0, (struct sockaddr *) &to, size);

	recvfrom(sd,(char *) &num, sizeof(int),0, (struct sockaddr *) &to, &size);
      	num = ntohl(num);

	printf("RECEIVED NUMBER: %d\n", num);
}
