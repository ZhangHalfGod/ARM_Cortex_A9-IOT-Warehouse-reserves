#include <stdio.h>
//头文件
#include <sys/stat.h>//open
//头文件
#include <fcntl.h>//open
//头文件 
#include <pthread.h>//pthread_t
#include<string.h>//memset()清理文件


int main()//主进程
{
	//定义数组存储文件的名字
	char name[100] = {0};
	//输入文件的名字
	scanf("%s", name);
	//打开文件
	int fd = open(name, O_RDONLY);
	// 			文件名字   访问的方式
	//判断是否正常打开文件
	if(fd > 0){
		//缓冲区存储读取的内容
		char buf[50] = {0};
		//分批次读取  
		while(read(fd, 		buf, 		  50) > 0){
				//标记      存储内容数组  读取文件的内容大小
				// > 0 读取内容
				
				//输出内容到屏幕
				printf("%s\n", buf);
				
				//清理buf内容,方便下次使用
				memset(buf, 	0, 		sizeof(buf));
				//    缓冲区	默认值	大小
			
		}
	}
	
	return 0;
}