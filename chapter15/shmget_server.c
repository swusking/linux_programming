#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define KEY 100
#define SEG_SIZE ((size_t)100)

#define oops(m, x) {perror(m); exit(x);}

int main(int argc, char *argv[]){
	int seg_id;
	char *seg_mem;
	time_t my_time;
	
	//建立对象
	if ( (seg_id = shmget(KEY, SEG_SIZE, IPC_CREAT|0777)) == -1)
		oops("shmget", -1);
	
	//分配内存
	if( (seg_mem = shmat(seg_id, NULL, 0)) == (void *)-1)
		oops("shmat", -1);
	
	time(&my_time); //获取时间
	strcpy(seg_mem, ctime(&my_time));
	
	while(1);
	
	shmctl(seg_id, IPC_RMID, NULL);//删除
	
	return 0;
}