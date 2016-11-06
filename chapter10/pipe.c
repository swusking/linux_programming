#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


#define BUFFER_SIZE 1024
#define oops(m,x) {printf(m); exit(x);}


int main(int argc, char *argv[]){
	
	int argList[2];
	char send_buffer[BUFFER_SIZE] = "";
	char recv_buffer[BUFFER_SIZE] = "";
	int len;
	
	int read_pipe = creat("read", 0755);
	int write_pipe = creat("write", 0755);
	
	argList[0] = read_pipe;
	argList[1] = write_pipe;
	
	
	printf("%d  %d", argList[0], argList[1]);
	if( pipe(argList) == -1)
		oops("pipe", -1);
	
	switch(fork()){
		case -1:
			oops("fork: ", -1);
			break;
			
		//子进程write
		case 0:
			close(argList[0]);
			if( dup2(argList[1], 1) == -1)
				oops("dups2: ", -1);
			
			execlp("cat", "who", "/etc/passwd", NULL);
			exit(0);
		//父进程read，读完后输出结果
		default:
			sleep(1);
			close(argList[1]);
			if( dup2(argList[0], 0) == -1)
				oops("dup2: ", -1);
			
			execlp("head", "head", "-1", NULL);
	}

	return 0;
}