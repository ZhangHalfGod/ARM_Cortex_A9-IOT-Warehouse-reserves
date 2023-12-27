#include "all.h"
//-------------定义全局变量 ： 大驼蜂  -----------------//
pthread_mutex_t  MutexLink;  	// 互斥锁-1  互斥的链表
pthread_cond_t   CondCmd;    	// 条件变量-1 控制命令的条件变量 
pthread_mutex_t  MutexCmd;   	// 同条件变量一起使用的互斥锁 
sem_t SemEnv, SemGoods, SemSms; // 信号量-1 环境的信号量、货物的信号量、异常信号量  

unsigned char CtlCmd;  //控制命令全局变量 
envinfo_t Env;         //环境数据全局变量
goods_t   Goods;       //货物数据全局变量

linknode_t *Link;	   //链表-1  链表指针 

//自定义函数： 创建多线程
int createAll(int *pfd)
{
	pthread_t tid_tra, tid_ana, tid_ref, tid_sql, tid_sms;
	pthread_t tid_req, tid_cmd;
	
	Link = createLink();	//链表-2  创建一个空链表
	if(NULL == Link)  return -1;

	//初始化 
	pthread_mutex_init(&MutexLink, NULL);  //互斥锁-2 
	pthread_cond_init(&CondCmd, NULL);     //条件变量-2
	pthread_mutex_init(&MutexCmd, NULL);   //同条件变量一起使用的互斥锁 
	sem_init(&SemEnv, 0, 0);   			   //环境的信号量-2
	sem_init(&SemGoods, 0, 0);			   //货物的信号量-2
	sem_init(&SemSms, 0, 0);			   //异常信号量-2 

	//创建7个线程 
	pthread_create(&tid_tra, NULL, pthread_transfer, pfd); //接收M0数据线程
	pthread_create(&tid_cmd, NULL, pthread_uart_cmd, pfd); //向M0发送命令线程
	pthread_create(&tid_ana, NULL, pthread_analysis, NULL); //分析线程
	pthread_create(&tid_ref, NULL, pthread_refresh, NULL);  //更新共享内存线程
	pthread_create(&tid_sql, NULL, pthread_sqlite, NULL);  //数据库操作线程
	pthread_create(&tid_sms, NULL, pthread_sms, NULL); //报警线程
	pthread_create(&tid_req, NULL, pthread_client_request, NULL);//处理消息队列线程

	pthread_join(tid_tra, NULL); //阻塞等待线程结束
	pthread_join(tid_ref, NULL); //阻塞等待线程结束

	return 0;
}
//应用层的入口函数main 
int main()
{
	int r; //返回值
	int sockfd, newsock; //套接字
	struct sockaddr_in seraddr;  // 服务器地址

	//A. 创建一个流式套接字(TCP) 
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	seraddr.sin_family = AF_INET;
	seraddr.sin_port = PORT; 
	seraddr.sin_addr.s_addr = IPV4; 
	//B. 绑定地址
	r = bind(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr)); 
	if(r < 0){ perror("bind() error"); return -1; }

	//C. 监听
	listen(sockfd, 10);

	while(1){
		printf("%s : 等待客户端的连接...\n", __func__);
		//D. 接收客户端的连接请求
		newsock = accept(sockfd, NULL, NULL);
		if(newsock < 0) break;

		pid_t pid = fork();  //创建一个子进程 	 
		if( pid == 0 ) //在子进程中 
		{	//E. 通信 -- 并发 
			createAll(&newsock);   
			exit(0);  // *** 子进程退出
		}else if(pid < 0){  //出错 
			perror("fork() error");
			break;
		}
		// 父进程回收子进程资源 不阻塞 
		waitpid(pid, NULL, WNOHANG);  
	}
	//F. 关闭套接字
	close(sockfd);
	return 0;
}
