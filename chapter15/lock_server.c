#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>

void lock_opeartion(int, int);

int main(int argc, char*argv[]){
	
	time_t now;
	int fd = 0;
	char *current_time;
	
	fd = open("test.txt", O_CREAT|O_WRONLY, 0644);

	while(1){
		time(&now);
		current_time = ctime(&now);
		lock_opeartion(fd, F_WRLCK);
		
		write(fd, current_time, strlen(current_time));
		
		lock_opeartion(fd, F_UNLCK);
	}


	return 0;
}

void lock_opeartion(int fd, int flag){
	struct flock lockinfo;
	
	lockinfo.l_type = flag;
	lockinfo.l_pid = getpid();
	lockinfo.l_start = 0;
	lockinfo.l_whence = SEEK_SET;
	lockinfo.l_len = 0;
	
	fcntl(fd, F_SETLKW, &lockinfo);
	
}