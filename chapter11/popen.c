#include <stdio.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]){
	
	FILE *pf = popen("cat /etc/passwd", "r");
	char buffer[BUFFER_SIZE];
	
	while( fgets(buffer, BUFFER_SIZE, pf) ){
		printf("%s", buffer);
	}
	
	pclose(pf);
	
	return 0;
}