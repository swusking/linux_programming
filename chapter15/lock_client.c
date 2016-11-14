#include <stdio.h>
#include <time.h>
#include <fcntl.h>

void lock_opeartion(int, int);

int main(int argc, char*argv[]){
	
	int fd = 0;
	char current_time[1024];
	
	fd = open("test.txt", O_CREAT|O_RDONLY);

	while(1){
		lock_opeartion(fd, F_RDLCK);
		
		read(fd, current_time, sizeof(current_time));
		printf("%s", current_time);
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