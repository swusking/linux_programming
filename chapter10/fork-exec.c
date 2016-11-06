#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>    //fork
#include <sys/wait.h>  //wait 
#include <stdlib.h>

int main(int argc, char *argv[]){
	
	int pid = fork();
	
	//如果是子进程
	if(pid == 0){
		close(1);
		creat("test.c", 0755);
		execlp("who", "who", NULL);
		exit(1);
		
	}else{
		wait(NULL);
		printf("done\n");
	}
	
	
	
	
	return 0;
}