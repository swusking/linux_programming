#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define ARGLIST_NUM 10 //参数个数
#define ARG_LEN 100    //每个参数长度

void exec(char *arglist[]);


int main(int argc, char *argv[]){
	
	char *arglist[ARGLIST_NUM];  //参数列表，注意这里没分配内存
	char arg_buffer[ARG_LEN];   //元素缓存
	int i=0, j=0; 
	//get_arglist(arglist);
	
	
	//循环获取参数
	while(i < ARGLIST_NUM){
		
		printf("arg[%d]: ", i);
		
		fgets(arg_buffer, ARG_LEN, stdin); //arglist没有分配内存不能直接赋值
		
		if( strcmp(arg_buffer, "\n") == 0 ){
			arglist[i] == NULL;
			exec(arglist);
			
			//释放空间
			for(j=0; j<i; j++){
				free(arglist[j]);
			}
			
			printf("\nnew start.............\n");
			i = 0;  //重新赋值
			continue;
		}else{
			//分配内存并赋值，fgets把'\n'也读进去了
			arg_buffer[strlen(arg_buffer) - 1] = '\0';
			if( (arglist[i] = malloc(strlen(arg_buffer))) == NULL){
				perror("");
				exit(1);
			}
			strcpy(arglist[i], arg_buffer);
			i++;
		}

	}

	
	
	printf("参数多了!\n");
	return 0;
	

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
