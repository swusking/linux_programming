#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define KEY 100
#define SEG_SIZE ((size_t)100)
#define BUFFER_SIZE 1024

#define oops(m, x) {perror(m); exit(x);}

int main(int argc, char *argv[]){
	int seg_id;
	char *seg_mem;
	char my_time[BUFFER_SIZE];
	
	//建立对象
	if( (seg_id = shmget(KEY, SEG_SIZE, IPC_CREAT|0777)) == -1)
		oops("shmget", -1);
	
	//建立内存
	if( (seg_mem = shmat(seg_id, NULL, 0)) == (void *)-1 )
		oops("shmat", -1);
	
	//读取内容
	strcpy(my_time, seg_mem);
	
	printf("%s\n", my_time);
	
	
	return 0;
}