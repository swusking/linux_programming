#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <utmp.h>
#include <stdlib.h>
#include <time.h>

void show_info(struct utmp *record_buffer);
void show_time(long timeval);

int main(void){
	
	struct utmp record_buffer;
	int record_size = sizeof(record_buffer);  //需要读取字节数
	
	int pf_utmp;      //文件指针
	
	if( (pf_utmp = open(UTMP_FILE, O_RDONLY)) == -1 ){
		perror(UTMP_FILE);
		exit(0);
	}
	
	while(read(pf_utmp, &record_buffer, record_size))
		show_info(&record_buffer);
	
	close(pf_utmp); //关闭指针
	
	return 0;
}

void show_info(struct utmp *record_buffer){
	if(record_buffer->ut_type != USER_PROCESS)  //这条信息如果不是已经登录用户，就退出
		return;
	
	printf("%s\t", record_buffer->ut_user);  //登录账户
	printf("%s\t", record_buffer->ut_line);    //tty
	show_time(record_buffer->ut_time);  //时间
}

void show_time(long timeval){
	char *cp;
	cp = ctime(&timeval);
	printf("%s", cp);   //时间后面有一个回车
}







