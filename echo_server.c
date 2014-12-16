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
	if(argc != 2){
		printf("USAGE: echo-server [port]\n");
		exit(1);
	}

	int queueLength = 5;
	int port = atoi(argv[1]);
	assert(port >= 0);

	struct sockaddr_in socketAddress;
	memset((char*)&socketAddress,0, sizeof(socketAddress));
	socketAddress.sin_family = AF_INET;
	socketAddress.sin_addr.s_addr = INADDR_ANY;
	socketAddress.sin_port = htons((u_short)port);

	int masterSocket = socket(PF_INET, SOCK_STREAM, 0);
	assert(masterSocket >= 0);

	int optval = 1;
	int err = setsockopt(masterSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&optval, sizeof(int));
	assert(err >= 0);
	err = bind(masterSocket, (struct sockaddr *)&socketAddress, sizeof(socketAddress));
	assert(err >= 0);
	err = listen(masterSocket, queueLength);
	assert(err >= 0);

	while(1){
		struct sockaddr_in client;
		int alen = sizeof(client);
		int clientSocket = accept(masterSocket, (struct sockaddr*)&client, (socklen_t *)&alen);
		assert(clientSocket >= 0);

		const int maxLength = 1024;
		char buf[maxLength +1];
		char newC, lastC;
		int curLength = 0;
		int n;

		while(curLength < maxLength && (n = read(clientSocket, &newC, sizeof(newC))) > 0){
			buf[curLength] = newC;
			curLength++;
			if(lastC == '\r' && newC == '\n'){
				break;
			}
			lastC = newC;
		}
		buf[curLength] = '\0';
		printf("Message Received: %s\n", buf);
		write(clientSocket, buf, strlen(buf));
		close(clientSocket);
	}

	return 0;
}