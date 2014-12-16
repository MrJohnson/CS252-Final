#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include<stdlib.h>

void iterativeServer(int masterSocket){
	while(1){
		struct sockaddr_in	clientIPAddr;
		int alen = sizeof(clientIPAddr);
		int slaveSocket = accept(masterSocket, (struct sockaddr *)&clientIPAddr, (socklen_t *)&alen);
		if(slaveSocket < 0){
			perror("accept");
			exit(1);
		}
		dispatchHTTP(slaveSocket);
	}
}

void forkServer(int masterSocket){
	while(1){
		struct sockaddr_in clientIPAddr;
		int alen = sizeof(clientIPAddr);
		int slaveSocket = accept(masterSocket, (struct sockaddr *)&clientIPAddr, (socklen_t *)&alen);
		
		if(slaveSocket < 0){
			perror("accept");
			exit(1);
		}

		int ret = fork();
		if(ret == 0){
			dispatchHTTP(slaveSocket);
			exit(0);
		} else if(ret < 0){
			perror("fork");
			exit(1);
		}

		close(slaveSocket);
	}
}

void * loopthread(void* socket){
	int masterSocket = (int)socket;
	while(1){
		struct sockaddr_in clientIPAddr;
		int alen = sizeof(clientIPAddr);;
		int slaveSocket = accept(masterSocket, (struct sockaddr *)&clientIPAddr, (socklen_t *)&alen);
		if(slaveSocket < 0){
			perror("accept");
			exit(1);
		}
		dispatchHTTP(slaveSocket);
	}
}

void poolOfThreads(int masterSocket){
	int i = 0;
	pthread_t threads[5];

	for(i = 0; i < 5; i++){
		pthread_create(&threads[i], NULL, loopthread, (void*)masterSocket);
	}
	loopthread((void*)masterSocket);
}

void createThreadForEachRequest(int masterSocket){
	while(1){
		struct socckadr_in clientIPAddr;
		int alen = sizeof(clientIPAddr);
		int slaveSocket = accept(masterSocket, (struct sockaddr *)&clientIPAddr, (socklen_t *)&alen);
		if(slaveSocket < 0){
			perror("accept");
			exit(1);
		}
		 pthread_attr_t attributes;
		 pthread_attr_init(&attributes);
		 pthread_attr_setdetachstate(&attributes, PTHREAD_CREATE_DETACHED);
		 pthread_create(NULL, &attributes, dispatchHTTP, slaveSocket);
	}
}