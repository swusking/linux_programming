#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <stdlib.h>

#define oops(m, x) {perror(m); exit(x);}


int main(int argc, char *argv[]){
	
	struct sockaddr_in server_addr, client_addr;
	int server_socket, client_socket;
	FILE *client_pf;
	
	time_t current_time;
	
	//建立socket
	server_socket = socket(PF_INET, SOCK_STREAM, 0);
	
	//填充IP信息
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_addr.sin_port = 6666;
	server_addr.sin_family = AF_INET;
	
	//绑定
	if( bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) != 0)
		oops("bind: ", -1);
	
	//监听
	if( listen(server_socket, 1) != 0 )
		oops("listen: ", -1);
	
	while(1){
		
		int len = sizeof(client_addr);
		if( (client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &len)) == -1)
			oops("accept: ", -1);
		
		client_pf = fdopen(client_socket, "w");
		if(client_pf == NULL)
			oops("fdopen: ", -1);
		
		
		current_time = time(NULL);
		fprintf(client_pf, "The time is : %s", ctime(&current_time));
		fclose(client_pf);
		
	}
	
	close(server_socket);
	close(client_socket);
	
	return 0;
}