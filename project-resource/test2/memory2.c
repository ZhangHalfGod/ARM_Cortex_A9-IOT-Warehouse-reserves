#include <stdio.h>
//新增的头文件
#include <sys/shm.h>
//新增的头文件
#include <sys/ipc.h>

int main()
{
	//共享内存的标识
	int shmid = 0;
	//获得共享内存
	shmid = shmget(666666, 100 * sizeof(char), 0666|IPC_CREAT);
	//    			 标识       大小               权限
	//获得共享内存的标识shmid
	//映射共享内存
	char *p = shmat(shmid, 	NULL, 	0);
	//				标识    空      读写
	//p是映射的地址
	//输出共享内存里面的内容
	printf("%s\n", p);
	//取消映射
	shmdt(p);
	//输出内容  
	printf("移除映射 ");
	
}