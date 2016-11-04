#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>


int main(int argc, char *argv[]){
	
	struct termios stty_info;
	
	if(argc != 2){
		printf("参数错误！\n");
	}
	
	if((tcgetattr(0, &stty_info)) == -1){
		perror("tcgetattr:");
		exit(1);
	}
	
	if(argv[1][0] == 'y' || argv[1][0] == 'Y'){
		stty_info.c_lflag |= ECHO;
	}
	
	if(argv[1][0] == 'n' || argv[1][0] == 'N'){
		stty_info.c_lflag &= ~ECHO;
	}
	
	if((tcsetattr(0, TCSANOW, &stty_info)) == -1){
		perror("tcsetattr:");
		exit(1);
	}
	
	return 0;
}