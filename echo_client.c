#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <assert.h>

int main(int argc, char** argv){
	if (argc != 4){
		printf("USAGE: echo-client [host] [port] [string]\n");
		exit(1);
	}

	char* host = argv[1];
	int port  = atoi(argv[2]);
	assert(port >= 0);
	char* echostring = argv[3];
	struct sockaddr_in socketAddress;

	memset((char*)&socketAddress, 0, sizeof(socketAddress));
	socketAddress.sin_family = AF_INET;
	socketAddress.sin_port = htons((u_short)port);

	struct hostent * ptrh = gethostbyname(host);
	assert(ptrh != NULL);
	memcpy(&socketAddress.sin_addr, ptrh->h_addr, ptrh->h_length);

	struct protoent* ptrp = getprotobyname("tcp");
	assert(ptrp != NULL);
	int sock = socket(PF_INET, SOCK_STREAM, ptrp->p_proto);
	assert(socket >+ 0);

	if(connect(sock, (struct sockaddr *)&socketAddress, sizeof(socketAddress)) < 0){
		perror("connect");
		exit(1);
	}

	write(sock, echostring, strlen(echostring));
	write(sock, "\r\n", 2);

	char buf[1024];
	int n = recv(sock, buf, sizeof(buf), 0);
	while(n > 0){
		write(1, buf, n);
		n = recv(sock, buf, sizeof(buf), 0);
	}

	close(sock);
	return 0;
}