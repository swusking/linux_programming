#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <pwd.h>   //getpwuid
#include <grp.h>   //getgrgid
#include <time.h>   //ctime
#include <string.h>

void ls_info(char *dirname);  

char *show_mode(int mode);   //mode 
char *show_uid(int uid);   //uid
char *show_gid(int gid);    //gid

int main(int argc, char *argv[]){
	int num = argc-1;
	if(argc == 1)
		ls_info(".");
	else{
		while(num){
			printf("%s:\n", argv[num]);
			ls_info(argv[num--]);
		}

	}
	
	return 0;
}

void ls_info(char *dirname){
	
	DIR *pd;   //目录
	struct dirent *dir_info;   //目录结构体
	struct stat file_stat;  //文件的属性结构体
	
	//打开目录
	if( (pd = opendir(dirname)) == NULL){
		perror(dirname);
	}
	
	//读取目录内容
	while( (dir_info=readdir(pd)) != NULL){
		//printf("%s\n", dir_info->d_name);
		//过滤
		if( (strcmp(dir_info->d_name, ".") == 0) || (strcmp(dir_info->d_name, "..") == 0) )
			continue;
		
		//获取属性
		
		char str[100];  
		sprintf(str, "%s/%s", dirname, dir_info->d_name);
		//注意文件路径！！！！
		if(stat(str, &file_stat) == -1){
			perror(dir_info->d_name);
			exit(1);
		}else{
			printf("%s  ", show_mode(file_stat.st_mode)); //mode
			printf("%-4d ", file_stat.st_nlink);  //hard link
			printf("%-10s", show_uid(file_stat.st_uid));  //UID			
			printf("%-10s", show_gid(file_stat.st_gid));  //GID
			printf("%-8ld  ", file_stat.st_size);  //size
			printf("%.12s  ", 4+ctime(&file_stat.st_mtime));   //mtime，%m.ns 输出占m列，但只取字符串中左端n个字符。这n个字符输出在m列的右侧，左补空格
			printf("%s\n", dir_info->d_name);    //name
		}
		
	}
	
	//关闭目录
	closedir(pd); 
}

char *show_mode (int mode){
	static char str[10];
	
	strcpy(str, "----------");  //重置。不然会和上次一样
	if(S_ISDIR(mode)) str[0] = 'd';
	if(S_ISCHR(mode)) str[0] = 'c';
	if(S_ISBLK(mode)) str[0] = 'b';
	if(S_ISFIFO(mode)) str[0] = 'p';
	if(S_ISLNK(mode)) str[0] = 'l';
	
	if(S_IRUSR & mode) str[1] = 'r';
	if(S_IWUSR & mode) str[2] = 'w';
	if(S_IXUSR & mode) str[3] = 'x';
	
	if(S_IRGRP & mode) str[4] = 'r';
	if(S_IWGRP & mode) str[5] = 'w';
	if(S_IXGRP & mode) str[6] = 'x';
	
	if(S_IROTH & mode) str[7] = 'r';
	if(S_IWOTH & mode) str[8] = 'w';
	if(S_IXOTH & mode) str[9] = 'x';
	
	if(S_ISUID & mode) str[1] = 's';
	if(S_ISGID & mode) str[5] = 's';
	if(S_ISVTX & mode) str[9] = 't';
	
	return str;
}

char* show_uid(int uid){
	struct passwd *username;
	static char str[10];    //设置静态变量，不然会被提示返回局部变量地址
	
	if((username = getpwuid(uid)) == NULL){   //搜索passwd没有找到就返回UID
		sprintf(str, "%s", uid);
		return str;
	}
	
	return username->pw_name;
}

char* show_gid(int gid){
	struct group *groupname;
	static char str[10];  
	
	if((groupname = getgrgid(gid)) == NULL){   //搜索group没有找到就返回GID
		sprintf(str, "%s", gid);
		return str;
	}
	
	return groupname->gr_name;
}


