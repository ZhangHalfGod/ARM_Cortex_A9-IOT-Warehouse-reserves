#include "all.h"
//短信报警线程
void *pthread_sms(void *p)
{
	while(1)
	{
		sem_wait(&SemSms); //信号量-3 P操作 ： 睡眠 
	
	}
}
