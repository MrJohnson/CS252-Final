#include <stdio.h>git 

int 
runCommand( char * command, char * outputBuffer, int maxBufferSize) 
{ 
	char* argv[2];
	int pid;
	int buf_file = fmemopen((void*) outputBuffer, 0666);
	int fdpipe[2];

	if(buf_file < 0){
		// error setting up buf_file
		perror("fmemopen");
		return -1;
	}



	// fork for child process
	pid = fork();
	if (pid == 0){
		// in child process
		pipe(fdpipe);
		fdpipe[0] = buf_file;
		fdpipe[1] = 1;
		argv[0] = command;			// set up argv
		argv[1] = NULL;
		execvp(argv[0], argv); 		// execute command
		perror("execvp");			// there was an error
		return -1;
	} else if (ret < 0) {
		// there was an error in fork
		perror("fork");
		return -1;
	} else {
		// parent process
		waitpid(pid, NULL);
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
       exit( -1 ); 
    }

    printf( "ls: %s\n", buffer );

    exit( 0 ); 
}

