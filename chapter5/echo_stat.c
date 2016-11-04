#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>


int main(int argc, char *argv[]){
	
	struct termios stty_info;
	
	if((tcgetattr(0, &stty_info)) == -1){
		perror("tcgetattr:");
		exit(1);
	}
	
	if( stty_info.c_lflag & ECHO)
		printf("ECHO : NO\n");
	else
		printf("ECHO : OFF\n");
	
	return 0;
}
