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

	int sfd, cfd, port_no;
	port_no = strtoul(argv[1], NULL, 10);

		/*
	Create your Socket do error checking
	Remember socket returns a socket descriptor
	SOCK_STREAM --->TCP
	or
	SOCK_DGRAM  --->UDP
	AF_INET ------->protocol/address family

	*/
	// if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	// {
		// perror("socket");
		// exit(2);
	// }

	struct sockaddr_in saddr = {0};
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port_no);
	saddr.sin_addr.s_addr = INADDR_ANY;// Accept any ip address
	
	//1. Bind is used for assigning port
	/* if (bind(sfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0) 
	{
		perror("bind");
		close(sfd);
		exit(3);
	} */
	
	//2. waits for incoming connection
	/* if (listen(sfd, 5) < 0) 
	{
		perror("listen");
		close(sfd);
		exit(4);
	} */

	//3. Accepts the incoming connection

	/* struct sockaddr_in caddr = {0};
	socklen_t len = sizeof(caddr);
	if ((cfd = accept(sfd, (struct sockaddr *)&caddr, &len)) < 0) 
	{
		perror("accept");
		exit(5);
	} */
	
// To make a program like ECHO
	char buf[20] = {0};
	int ret = 0;
	if ((ret = recv(cfd, buf, sizeof(buf), 0)) < 0)
	{
		perror("recv");
		close(cfd);
		close(sfd);
		exit(6);
	}

	if (send(cfd, buf, ret, 0) < 0)
	{
		perror("send");
		close(cfd);
		close(sfd);
		exit(7);
	}

	close(cfd);
	close(sfd);

	return 0;
}
