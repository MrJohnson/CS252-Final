int 
runCommand( char * command, char * outputBuffer, int maxBufferSize) 
{ 
	char** args
    
	int ret = fork();
	int buf_file = fmemopen((void*) outputBuffer, 0666);



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

