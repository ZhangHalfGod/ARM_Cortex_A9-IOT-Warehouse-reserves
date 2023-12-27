#include "all.h"
//接收M0数据线程
void *pthread_transfer(void *p)
{
	if(NULL == p){
		printf("%s : 创建此线程时忘记传参\n", __func__);
		pthread_exit(0);
	}
	int fd = *((int *)p); //获得参数值
	data_t a;   //envinfo_t a;   //存储接收到数据
	int r;
	while(1){
		r = recv(fd, &a, sizeof(a), 0);  //A. 接收一次数据
		if(r <= 0)  break;
		//printf("%s : %d %d.%d ... %d\n", 
		//		__func__, a.devno, a.temp[0],
		//		a.temp[1], a.voltage); //临时测试
	
		pthread_mutex_lock(&MutexLink);		//互斥锁-3 ： 上锁	
		//B.插入到链表中  链表-3 
		if( insertLinkEnd(Link, a) )
			printf("%s : insert link ok\n", __func__);
		pthread_mutex_unlock(&MutexLink);	//互斥锁-4 ： 解锁 
	}
	printf("感知层已下线\n");
	//链表-5  释放链表
	freeLink(Link);

	exit(0);
}
