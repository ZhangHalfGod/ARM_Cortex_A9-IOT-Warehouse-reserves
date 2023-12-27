#include <stdio.h>
//头文件
#include <sys/shm.h>
/*
思考：

映射共享内容？


思考：

两个进程通过共享内存通信？

线程1：  写共享内存     test.c 

线程2：  读共享内存     test2.c (请新建)
*/
int main()
{
	//定义标识
	int shmid1 = 0;
	//创建共享内存
	shmid1 = shmget(666666, 100 * sizeof(char), 0666|IPC_CREAT);
	//				数         大小         权限    创建  
	//返回值是共享内存的标识
	//输出内容
	printf("shmid1 : %d\n", shmid1);
	
	//映射共享内存
	char *p = shmat(shmid1, 		NULL, 		0);
	//				共享内存的标识
	//p是映射的共享内存的地址，通过p访问共享内存
	
	//输入字符串存储到共享内存
	scanf("%s", p);
	
	//解除映射
	shmdt(p);
	//参数1：是共享内存的标识地址
	//输出内容  
	printf("映射解除\n");
	
	return 0;
}