#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv){
	
	char buffer[BUFFER_SIZE];
	
	fgets(buffer, BUFFER_SIZE, stdin);
	printf("%s", buffer);
	

	
	
	close(0);
	
	//这儿打开的是0标识符，所以用if(!pf)会出文件
	int pf = open("/etc/passwd", O_RDONLY);
	printf("%d", pf);
	
	fgets(buffer, BUFFER_SIZE, stdin);
	printf("%s", buffer);
	
	return 0;
}