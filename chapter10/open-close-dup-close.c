#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv){
	
	char buffer[BUFFER_SIZE];
	
	fgets(buffer, BUFFER_SIZE, stdin);
	printf("%s", buffer);
	


	int pf = open("/etc/passwd", O_RDONLY);
	printf("pf: %d\n", pf);
	
	close(0);
	
	int newpf = dup(pf);
	printf("newpf: %d\n", newpf);
	
	close(pf);
	
	
	
	fgets(buffer, BUFFER_SIZE, stdin);
	printf("%s", buffer);
	
	return 0;
}