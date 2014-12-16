#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int 
runCommand( char * command, char * outputBuffer, int maxBufferSize) 
{
	int i =0;
	char* argv[2];
	int pid;
	int fdpipe[2];
	if(pipe(fdpipe) < 0){
		perror("pipe");
		return -1;
	}

	
	pid = fork();	// fork for child process
	if (pid == 0){
		// in child process
		close(fdpipe[0]);		// don't need read-end
		dup2(fdpipe[1], 1);		// send stdout to pipe
		dup2(fdpipe[1], 2);		// set stderr to pipe
		argv[0] = command;		// set up argv
		argv[1] = NULL;
		

		execvp(argv[0], argv);		// execute command
		perror("execvp");		// there was an error
		return -1;
	} else if (pid < 0) {
		// there was an error in fork
		perror("fork");
		return -1;
	} else {
		// parent process
		waitpid(pid, NULL, 0);
		close(fdpipe[1]);  // write-end of pipe no longer needed
		while(read(fdpipe[0], outputBuffer, maxBufferSize) != 0){}
		close(fdpipe[0]);
		return 0;
	}
}

int 
main() 
{ 
  // The output of "ls" will be stored in buffer 
  char buffer[ 1024 ];

  if ( runCommand( "ls", buffer, 1024 ) < 0 ) { 
    perror("runCommand" ); 
    exit(-1); 
  }

  printf( "ls: %s\n", buffer );

  exit( 0); 
}

