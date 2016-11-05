#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

#define SELLPTIME 2

int get_resopnse(void);
void save_stty(void);   //保存终端属性
void renew_stty(void);  //回复终端属性
void set_stty(void);  //设置非规范模式和单字符输入
void set_flags(void); //设置非阻塞
void ctrl_c_init(int); //CTRL+C

static struct termios stty_info_buffer;
static flags;

int main(int argc, char *argv[]){
	
	int answer=2;  //0:no, 1:yes，2:没选择
	
	save_stty(); //保存终端属性
	set_stty();  //设置当前环境的终端属性
	set_flags();  //设置非阻塞
	signal(SIGINT, ctrl_c_init);  //CTRL+C
	signal(SIGQUIT, SIG_IGN);  //忽略CTRL_\
	
	answer = get_resopnse();
	
	if(answer == 1)
		printf("YES\n");
	if(answer == 0)
		printf("NO\n");
	if(answer == 2)
		printf("NOT CHOOSE\n");
	
	renew_stty(); //恢复磁盘属性
	return 0;
}

int get_resopnse(void){
	int num = 3;  //有3次输入的机会
	char answer;

	printf("%s: ", "Do you want to go dead?");
	fflush(stdout);   //强制把输出缓冲区的数据输出
	
	while(num > 0){
		sleep(SELLPTIME);  //睡眠2秒，期间如果没输入则继续睡两秒
		answer = getchar();  //因为是非阻塞，所以没有数据会直接跳过
		switch(answer){
			case 'y':
			case 'Y': return 1;
			case 'n':
			case 'N': return 0;
		}
		putchar('\a');
		num--;
	}
	
	return 2;
}

void save_stty(void){
	flags = fcntl(0, F_GETFL);    //获取磁盘属性
	tcgetattr(0, &stty_info_buffer);  //把设备终端保存下来以便恢复
}

void renew_stty(void){
	tcsetattr(0, TCSANOW, &stty_info_buffer);  //恢复
	fcntl(0, F_SETFL, flags);//恢复磁盘属性
}

void set_stty(void){
	struct termios stty_info;
	tcgetattr(0, &stty_info);
	stty_info.c_lflag &= ~ICANON;  //关闭规范模式
	stty_info.c_cc[VMIN] = 1;  //设单字符模式，一个字符一个字符输入
	stty_info.c_lflag &= ~ECHO;  //关闭回显
	tcsetattr(0, TCSANOW, &stty_info);
}

void set_flags(void){
	int flags;
	flags = fcntl(0, F_GETFL);
	flags |= O_NDELAY;  //关闭阻塞
	fcntl(0, F_SETFL, flags);
}

void ctrl_c_init(int signum){
	renew_stty();
	exit(1);
}

