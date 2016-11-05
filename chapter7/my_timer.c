/*******
**定时器
**参数两个（毫秒）：开始时间，间隔时间
**定时完毕输出“timer over!”
*******/

#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <signal.h>

void set_timer(int start_time, int interval_time);
void timer_fuc(int signum);

int main(int argc, char *argv[]){
	
	if(argc != 3){
		printf("参数错误\n");
	}
	
	set_timer( atoi(argv[1]), atoi(argv[2]));
	while(1)
		pause();
	return 0;
}


void set_timer(int start_time, int interval_time){
	signal(SIGALRM, timer_fuc);
	
	struct itimerval new_timer;
	int start_sec=0, start_usec=0;
	int interval_sec=0, interval_usec=0;
	
	start_sec = start_time / 1000;   //秒
	start_usec = (start_time % 1000) * 1000L; //毫秒
	
	new_timer.it_value.tv_sec = start_sec;
	new_timer.it_value.tv_usec = start_usec;
	  
	interval_sec = interval_time / 1000;  //秒
	interval_usec = (interval_time % 1000) * 1000L;   //毫秒
	
	new_timer.it_interval.tv_sec = interval_sec;
	new_timer.it_interval.tv_usec = interval_usec;
		
	setitimer(ITIMER_REAL, &new_timer, NULL);
}


void timer_fuc(int signum){
	
	printf("timer over!\n");
}