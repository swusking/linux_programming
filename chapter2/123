#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUFFER_SIZE 512

int main(int argc, char *argv[]){
	
	int pf_sou, pf_des;   //源文件，目标文件
 	char buffer[BUFFER_SIZE]; //缓冲区
	int read_num;   //已读取的字节数
	
	if(argc != 3){
		printf("参数不够！\n");
		exit(1);
	}
	
	if( (pf_sou = open(argv[1], O_RDONLY)) == -1  ){
		perror(argv[1]);
		exit(1);
	}
	
	if( (pf_des = creat(argv[2], 0755)) == -1 ){
		perror(argv[2]);
		exit(1);
	}
	
	while( (read_num = read(pf_sou, buffer, BUFFER_SIZE)) >0){
		if(write(pf_des, buffer, read_num) != read_num){
			perror("write error ");
			exit(1);
		}
	}
	
	if(read_num == -1){
		perror("read error ");
		exit(1);
	}
	
	close(pf_sou);
	close(pf_des);
	
	
	return 0;
}