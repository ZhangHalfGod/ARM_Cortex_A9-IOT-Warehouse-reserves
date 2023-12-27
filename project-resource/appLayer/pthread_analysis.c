#include "all.h"
//分析线程
void *pthread_analysis(void *p)
{
	data_t a; //存储 链表中数据域值 
	while(1){
		pthread_mutex_lock(&MutexLink);		//互斥锁-3 ： 上锁  
		//A.从链表中取出第一个节点数据 链表-4 
		if( deleteLinkHead(Link, &a) == 0  ) //失败
		{
			pthread_mutex_unlock(&MutexLink); 
			sleep(1);
			continue;
		}
		pthread_mutex_unlock(&MutexLink);	//互斥锁-4 ： 解锁 
		//B.分析数据 a
		if(a.goods.type != 'g') {//环境 
			printf("%s : get env\n", __func__);
			Env = a.env;	  //传递-环境数据
			sem_post(&SemEnv);//信号量-4  V操作：唤醒线程
		}
		if(a.goods.type == 'g') {	//货物
			printf("%s : get goods\n", __func__);
			Goods = a.goods; 	 //传递-货物数据
			sem_post(&SemGoods); //信号量-4 V操作：唤醒线程 
		}	
		{	//异常
			sem_post(&SemSms);  //信号量-4 V操作：唤醒线程 
		}
	}
}
