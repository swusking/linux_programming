#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define oops(m, x) {perror(m); exit(x);}

void show_data(int fd);

int main(int argc, char *argv[]){
	int fd1, fd2;  //两个文件描述符
	fd_set read_fds;  //select的read参数
	struct timeval timeout;  //超时设置
	int maxfd;
	int retval;
	
	if( (fd1 = open(argv[1], O_RDONLY)) == -1)
		oops("open", -1);
	
	if( (fd2 = open(argv[2], O_RDONLY)) == -1)
		oops("open", -1);
	maxfd = (fd1 > fd2) ? fd1 : fd2;
	maxfd++;
	
	while(1){
		FD_ZERO(&read_fds);
		FD_SET(fd1, &read_fds);
		FD_SET(fd2, &read_fds);
		
		timeout.tv_sec = atoi(argv[3]);
		timeout.tv_usec = 0;
		
		retval = select(maxfd, &read_fds, NULL, NULL, &timeout);
		if(retval == -1)
			oops("select", -1);
		
		if(retval > 0){
			if(FD_ISSET(fd1, &read_fds))
				show_data(fd1);
			if(FD_ISSET(fd2, &read_fds))
				show_data(fd2);
		}else{
			//超时
			printf("time out......\n");
		}
		
	}
	return 0;
}


void show_data(int fd){
	
	int len;
	char buffer[BUFFER_SIZE];
	memset(buffer, 0, BUFFER_SIZE);
	
	len = read(fd, buffer, BUFFER_SIZE);
	if( len == -1 )
		oops("read", -1);
	
	write(1, buffer, len);
	write(1, "\n", 1);
	
}