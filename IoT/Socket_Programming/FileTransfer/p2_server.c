#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>


int sendfile(char *fname, int cfd)
{
	int fd;

	if ((fd = open(fname, O_RDONLY, 0)) < 0)
	{
		perror("open");
		return -1;
	}

	int ret = 0;
	char buf[128] = {0};
	int t_bytes = 0;
	while ((ret = read(fd, buf, sizeof(buf))) > 0)
	{
		t_bytes += ret;
		if (send(cfd, buf, ret, 0) < 0)
		{
			perror("send");
			close(fd);
			return -1;
		}
	}

	if (ret < 0)
		perror("read");

	printf("%d bytes sent\n", t_bytes);
	close(fd);
	return ret;
}


int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("Usage: %s <port_no>\n", argv[0]);
		exit(1);
	}

	int sfd, cfd, port_no;
	port_no = strtoul(argv[1], NULL, 10);

	if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
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

	if (listen(sfd, 5) < 0)
	{
		perror("listen");
		close(sfd);
		exit(4);
	}

	struct sockaddr_in caddr = {0};
	socklen_t len = sizeof(caddr);
	if ((cfd = accept(sfd, (struct sockaddr *)&caddr, &len)) < 0)
	{
		perror("accept");
		close(sfd);
		exit(5);
	}

	char fname[20] = {0};
	if (recv(cfd, fname, sizeof(fname) - 1, 0) < 0)
	{
		perror("recv");
		close(cfd);
		close(sfd);
		exit(6);
	}

	int ret;
	if ((ret = sendfile(fname, cfd)) < 0)
		printf("File transfer failed\n");
	else
		printf("File transferred successfully\n");

	close(cfd);
	close(sfd);

	if (ret < 0)
		exit(7);

	return 0;
}
