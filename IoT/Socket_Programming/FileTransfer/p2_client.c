#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>


int recv_file(char *fname, int cfd)
{
	int fd, ret = 0;
	char path[32] = {0};

	snprintf(path, sizeof(path), "data/%s", fname);

	if ((fd = open(path, O_CREAT|O_WRONLY|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)) < 0)
        {
                perror("open");
                return -1;
        }

	char buf[128] = {0};
	int t_bytes = 0;
	while ((ret = recv(cfd, buf, sizeof(buf), 0)) > 0)
	{
		t_bytes += ret;
		if (write(fd, buf, ret) < 0)
		{
			perror("write");
			close(fd);
			return -1;
		}
	}

	if (ret == -1)
		perror("recv");

	printf("%d bytes received\n", t_bytes);
	close(fd);

	return ret;
}


int main(int argc, char *argv[])
{
	if (argc < 4)
	{
		printf("Usage: %s <serv_ip> <serv_port> <fname>\n", argv[0]);
		exit(1);
	}

	int cfd, serv_port;
	serv_port = strtoul(argv[2], NULL, 10);

	if ((cfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket");
		exit(2);
	}

	struct sockaddr_in saddr = {0};
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(serv_port);
	saddr.sin_addr.s_addr = inet_addr(argv[1]);

	if (connect(cfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
	{
		perror("connect");
		close(cfd);
		exit(3);
	}

	if (send(cfd, argv[3], strlen(argv[3]) + 1, 0) < 0)
	{
		perror("send");
		close(cfd);
		exit(4);
	}

	if (recv_file(argv[3], cfd) < 0)
		printf("Error while receiving file\n");
	else
		printf("File received successfully\n");

	close(cfd);

	return 0;
}
