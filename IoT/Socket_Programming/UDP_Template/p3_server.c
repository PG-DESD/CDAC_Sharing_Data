#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <arpa/inet.h>


int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("Usage: %s <port_no>\n", argv[0]);
		exit(1);
	}

	int sfd, port_no;
	port_no = strtoul(argv[1], NULL, 10);

	if ((sfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("socket");
		exit(2);
	}

	struct sockaddr_in saddr = {0};
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port_no);
	saddr.sin_addr.s_addr = INADDR_ANY;
	
	if (bind(sfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
	{
		perror("bind");
		close(sfd);
		exit(3);
	}

	char buf[20] = {0};
	int ret = 0;
	struct sockaddr_in caddr = {0};
	socklen_t len = sizeof(caddr);
	if ((ret = recvfrom(sfd, buf, sizeof(buf), 0, (struct sockaddr *)&caddr, &len)) < 0)
	{
		perror("recvfrom");
		close(sfd);
		exit(6);
	}

	if (sendto(sfd, buf, ret, 0, (struct sockaddr *)&caddr, len) < 0)
	{
		perror("sendto");
		close(sfd);
		exit(7);
	}

	close(sfd);

	return 0;
}
