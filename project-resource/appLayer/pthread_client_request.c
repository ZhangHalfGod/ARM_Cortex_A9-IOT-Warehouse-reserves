#include "all.h"
//处理消息队列线程
void *pthread_client_request(void *p)
{
	struct msg msg_buf;
	int msgid;
	key_t key = 0;
	int r;

	key = ftok("/app", 'g');   //获得一个键值 
	if(key < 0){	perror("ftok() error"); pthread_exit(0);	}
	//A. 创建一个消息队列
	msgid  = msgget(key, IPC_CREAT|0666);
	if(msgid < 0){	perror("msgget() error");	pthread_exit(0);   }
	while(1){
		//B. 阻塞等待接收消息    过滤类型=1L
		r = msgrcv(msgid, &msg_buf, sizeof(msg_buf)-sizeof(long), 1L, 0);
		if(r < 0) break;
		
		printf("%s : %ld %ld %#x\n\n", __func__, msg_buf.type,
				msg_buf.msgtype, msg_buf.text[0]);
	
		pthread_mutex_lock(&MutexCmd);   //上锁 
		CtlCmd = msg_buf.text[0];        //传递：M0板的控制命令 
		pthread_cond_signal(&CondCmd);   //条件变量-4 唤醒线程
		pthread_mutex_unlock(&MutexCmd); //解锁 
	}
	//C. 删除消息队列
	msgctl(msgid, IPC_RMID, NULL);
}
