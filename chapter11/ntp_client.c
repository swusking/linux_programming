#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>  //memset


#define oops(m, x) {perror(m); exit(x);}
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]){
	
	struct sockaddr_in server_addr;
	int client_socket;
	FILE *client_pf;
	
	char recv_buffer[BUFFER_SIZE];
	
	//建立socket
	client_socket = socket(PF_INET, SOCK_STREAM, 0);
	
	//填充IP信息
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_addr.sin_port = 6666;
	server_addr.sin_family = AF_INET;
	

	//连接
	if( connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1 )
		oops("connect: ", -1);
	
	
	memset(recv_buffer, 0, BUFFER_SIZE);
	//读数据
	client_pf = fdopen(client_socket, "r");
	fgets(recv_buffer, BUFFER_SIZE, client_pf);
	
	printf("%s\n", recv_buffer);
	
	close(client_socket);
	
	return 0;
}