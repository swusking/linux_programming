#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

#define BUFFER_SIZE 512

void pwd(char *filename);
char *inode_to_dirname(ino_t inode);
ino_t get_inode(char *filename);

char dir_path[BUFFER_SIZE]="";

int main(int argc, int *argv[]){
	
	int path_len = 0;
	
	pwd(".");
	
	//下面只是为了将最后面的"/"删除
	path_len = strlen(dir_path);
	dir_path[path_len-1] = '\0';
	
	printf("%s\n", dir_path);
	
	return 0;
}

void pwd(char *filename){
	
	ino_t current_inode;
	current_inode = get_inode(".");
	
	//char str[BUFFER_SIZE]="";
	char dir_temp[BUFFER_SIZE]="";
	
	strcpy(dir_temp, dir_path);  //把路径赋值下来方便下面输出
	
	if(get_inode("..") == current_inode){
		sprintf(dir_path, "/%s", dir_temp);
		return;
	}else{
		chdir("..");
		
		//sprintf(st, "%s", inode_to_dirname(current_inode));
		//printf("%s\n", st);
		
		//如果把dir_temp换为dir_path，你会发现那两个%s会一样，因为dir_path先被赋值了，然后又被自己赋值了一次
		sprintf(dir_path, "%s/%s",  inode_to_dirname(current_inode), dir_temp);
		pwd(".");
	}
}

//返回文件的inode号，只在文件在当前目录下有效
ino_t get_inode(char *filename){
	struct stat current_dir_stat;  //获取当前目录中“.”的inode号
	
	//打开当前filename所在目录
	if(stat(filename, &current_dir_stat) == -1){
		perror(filename);
		exit(1);
	}
	
	return current_dir_stat.st_ino;
}

//打开当前目录，查看当前目录下是否有和参数inode相同的文件，如果有返回dirname
char *inode_to_dirname(ino_t inode){
	
	DIR *current_dir;    // 打开当前目录
	struct dirent *current_dir_info; // 当前目录的信息
	
	//打开当前目录
	if( (current_dir = opendir(".")) == NULL){
		perror(".");
		exit(1);
	}
	
	//获取父目录的inode号
	while((current_dir_info = readdir(current_dir)) != NULL){
		if( current_dir_info->d_ino == inode ){			
			close(current_dir);
			return current_dir_info->d_name;   //返回filename

		}
	}

	//获取inode失败
	if(current_dir_info == NULL){
		perror(".");
		exit(2);
	}
}