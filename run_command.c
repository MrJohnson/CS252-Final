#include <stdio.h>
#include <stdlib.h>

int 
runCommand( char * command, char * outputBuffer, int maxBufferSize) 
{
	int i =0;
  char* argv[2];
	int pid;
	int fdpipe[2];
  pipe(fdpipe);

	// fork for child process
	pid = fork();
	if (pid == 0){
		// in child process
    argv[0] = command;        // set up argv
    argv[1] = NULL;
    close(fdpipe[0]);

    dup2(fdpipe[1], 1);       // send stdout to pipe
    dup2(fdpipe[1], 2);       // set stderr to pipe

		execvp(argv[0], argv); 		// execute command
		perror("execvp");			// there was an error
		return -1;
	} else if (pid < 0) {
		// there was an error in fork
		perror("fork");
		return -1;
	} else {
		  // parent process
		  waitpid(pid, NULL);
      close(fdpipe[1]);  // close the write end of the pipe in the parent
      while(read(fdpipe[0], outputBuffer, maxBufferSize) != 0){
    }

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

