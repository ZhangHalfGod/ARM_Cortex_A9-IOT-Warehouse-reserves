#include "all.h"
// 向M0发送命令线程
void *pthread_uart_cmd(void *p)
{
	if(NULL == p){
		printf("%s : 创建此线程时忘记传参\n", __func__);
		pthread_exit(0);
	}
	int fd = *((int *)p);  //获得传参值
	while(1)
	{
		pthread_mutex_lock(&MutexCmd); //上锁
		pthread_cond_wait(&CondCmd, &MutexCmd);//条件变量-3  睡眠+解锁 
		//sleep(2);  //临时测试 
		//unsigned char cmd = 0x61;  //临时测试 开灯 
		if( send(fd, &CtlCmd, sizeof(CtlCmd), 0) <= 0 ) //A. 发送M0的控制命令
			break;
		pthread_mutex_unlock(&MutexCmd);  //解锁 

		printf("%s : send a cmd\n\n", __func__);

	}
}
