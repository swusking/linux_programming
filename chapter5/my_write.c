#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 512

//向终端发送消息，不是向某人发送消息
int main(int argc, char *argv[]){
	
	int p_dev;
	char send_buffer[BUFFER_SIZE];
	
	if(argc != 2){
		printf("参数错误！");
		exit(1);
	}
	
	if( (p_dev = open(argv[1], O_WRONLY)) == -1){
		perror(argv[1]);
		exit(1);
	}
	
	//EOF也可以退出
	while(fgets(send_buffer, BUFFER_SIZE, stdin) != NULL){
		if(write(p_dev, send_buffer, strlen(send_buffer)) != strlen(send_buffer)){
			perror("send:");
		}
	}
	
	close(p_dev);
	return 0;
}