/*****
这个比上个单元的更加完整。shell效果还是不错
忽略信号SIGINT, SIGQUIT
*****/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#define ARGLIST_NUM 10 //参数个数
#define ARG_LEN 100    //每个参数长度

#define BUFFER_SIZE 10 //命令行大小
#define ADD_BUFFER_SIZE 5  //命令行不够再加5

void exec(char *arglist[]);  //执行程序
char *get_cmd(void);      //获取一整条命令，包括参数
char **get_arglist(char *current_cmd);  //把命名拆分成到arglist数组中

int main(int argc, char *argv[]){
	
	char *current_cmd;    //存储输入的每条命令
	char **arglist;  //参数列表，注意这里没分配内存

	int i=0; 

	//忽略信号
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	
	while( (current_cmd = get_cmd() ) != NULL){
		if( strcmp(current_cmd, "") == 0)
			continue;
		
		arglist = get_arglist(current_cmd);  //获取参数数组
		
		//while(arglist[i] != NULL)
		//	printf("%s\n", arglist[i++]);
		
		//执行程序
		exec(arglist);
		
		//释放空间
		while(arglist[i] != NULL)
			free(arglist[i++]);
	}
	
	return 0;
}

char **get_arglist(char *current_cmd){
	static char *arglist[ARGLIST_NUM];  //要返回的字符串数组
	char arg_buffer[ARG_LEN];  //缓存每个元素
	char *cmd_buffer;   //把命令复制到这里
	int i=0, arg_num=0;
	
	//分配空间，并赋值命令
	cmd_buffer=malloc(strlen(current_cmd));
	strcpy(cmd_buffer, current_cmd);
	//printf("%s", cmd_buffer);
	//list -a -l 
	while(1){
		if(cmd_buffer[i] == ' ' || cmd_buffer[i] == '\0'){
			arglist[arg_num] = malloc(i+1);  //分配
			strncpy(arglist[arg_num], cmd_buffer, i);  //赋值
			arglist[arg_num][i] = '\0';   //添加'\0'
			
		//	printf("%s\n", arglist[arg_num]);
			if(cmd_buffer[i] == '\0'){
				arglist[arg_num+1] = NULL;
				return arglist;
			}

			
			cmd_buffer = cmd_buffer+i+1;  //把指针移到空格后面那一字节
			arg_num++;
			i=0;
		}
		i++;
	}

}


char *get_cmd(void){
	char *currnet_cmd;
	
	int buffer_flag = BUFFER_SIZE;  //用来重新分配内存
	int c_num = 0;  //已输入字符数的数量
	char c;  //缓存输入字符
	
	currnet_cmd = malloc(BUFFER_SIZE); //先分配一个小内存,10个字符
	
	printf("[SKING_SHELL] ");
	
	while( (c = fgetc(stdin)) != EOF){
		
		//如果是回车则直接退出子程序
		if(c == '\n'){
			currnet_cmd[c_num] = '\0';
			return currnet_cmd;
		}
		
		currnet_cmd[c_num++] = c;
		
		//重新分配内存
		if( ((c_num - BUFFER_SIZE) % ADD_BUFFER_SIZE) == 0){
			currnet_cmd = realloc(currnet_cmd, buffer_flag+ADD_BUFFER_SIZE);
			buffer_flag += ADD_BUFFER_SIZE;
		}

	}
	
	return NULL;
}

void exec(char *arglist[]){
	
	int ret_pid = 0;  //子进程PID
	int ret_val = 0;  //子进程exit返回值
	
	ret_pid = fork();  //开启新进程
	switch(ret_pid){
		case 0:         //子进程执行程序
			if( execvp(arglist[0], arglist) == -1){
				perror(arglist[0]);
				exit(2);
			}	
			_exit(1);
			
		case -1:  //错误
			perror("fork failed!");
			exit(1);
			
		default: //父进程
			while(ret_pid != wait(&ret_val));  //死循环等待子进程结束
	}
	
}
