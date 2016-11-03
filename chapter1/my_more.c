/**********************
 *2016.12.2
 *有重定向功能
 *
 *
 **********************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAGE_LEN 24     //每页24行
#define LINE_LEN 512   //每行最多512字节

void more(FILE *);

int main(int argc, char *argv[]){
	char buffer[LINE_LEN];
	
	FILE *pf;
	
	if(argc == 1){
		//fgets(buffer, LINE_LEN, stdin);
		more(stdin);    //用重定向是从这里输入的
	}else{ 
		//strcpy(buffer, argv[1]);
		while(--argc){
			if((pf = fopen(*++argv, "r")) != NULL){
				more(pf);
				fclose(pf);
			}else
				break;
		}
	}
	/*
	if( (pf = fopen(buffer, "r")) == NULL ){
		printf("打开文件失败！\n");
		return 0;
	}
	more(pf);
	*/
	return 0;
}

void more(FILE *pf){
	
	FILE *ptty; //从/dev/tty获取数据
	char line_buffer[LINE_LEN];   //存放文件读出来的一行内容
	int line_read_num = 0;  //已读的行数
	int getchar_num = 0;   
	char c;
	
	//打开文件

	
	if((ptty = fopen("/dev/tty", "r")) == NULL){
		printf("打开tty失败！\n");
		exit(0);
	}
	
	//循环输出文件内容，每输出24行则等待输入，没到24行则退出程序
	while(fgets(line_buffer, LINE_LEN, pf)){
		
		//如果输出了24行
		if(line_read_num == PAGE_LEN){
			printf("\n\033[7m more? \033[m");
			while((c = getc(ptty)) != EOF){   //这儿的数据是/dev/tty传入的
				if(c == 'q'){
					fclose(pf);
					exit(0);
				}
				else if(c == '\n'){
					getchar_num = 1;
					break;
				}	
				else if(c == ' '){
					getchar_num = 24;
					break;
				}
			}
			
			line_read_num -= getchar_num;
		}
		
		//
		if(fputs(line_buffer, stdout) == EOF){
			exit(0);
		}
		
		line_read_num++;	
	}
	
	fclose(ptty);
	fclose(pf);
}
