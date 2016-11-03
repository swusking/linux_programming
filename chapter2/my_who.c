#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <utmp.h>
#include <stdlib.h>
#include <time.h>

#define RECORD_NUM 5
#define RECORD_BUF (sizeof(struct utmp))

void show_info(struct utmp *record_buffer);
void show_time(long timeval);
struct utmp *get_next_record(void);  //获取下一个记录

int pf_utmp;      //文件指针

char record_buffer[RECORD_NUM * RECORD_BUF];  //10个数据的总大小

int current_num=0;     //从文件中读了多少个数据过来，可能不到10个
int read_num=0;   //当前已经读到第几个数据了
int flag = 0; //是否把文件内容读完了

int main(void){
	
	struct utmp *record;
	
	//打开文件
	if( (pf_utmp = open(UTMP_FILE, O_RDONLY)) == -1 ){
		perror(UTMP_FILE);
		exit(1);
	}
	
	//while(read(pf_utmp, &record_buffer, record_size))
	//	show_info(&record_buffer);
	
	while( (record = get_next_record()) != NULL){
		show_info(record);
	}
	
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

struct utmp *get_next_record(){
	struct utmp *utmp_buffer;  
	
	if(current_num == read_num && flag)
		return NULL;
	
	//当读完了缓存中的5个数后再读取
	if(current_num == read_num){
		int size = read(pf_utmp, record_buffer, RECORD_NUM * RECORD_BUF); //读取5个数据
		current_num = size / RECORD_BUF; //里面真正读了有多少个数
		if(current_num < 5)   //不足10个，说明已经读完了
			flag = 1;
		if(current_num == 0)  //没有数据直接退出
			return NULL;
			
		read_num = 0;  //置0
	}
	
	utmp_buffer = (struct utmp*)&record_buffer[read_num * RECORD_BUF];
	read_num++;
	return utmp_buffer; //返回当前读取的数值
	
}




