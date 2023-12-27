#include "all.h"
//感知层的入口函数main
int main()
{
	int r; //返回值
	int sockfd;   //套接字
	pthread_t tid_info, tid_ctl; //线程Id存储变量 
	struct sockaddr_in seraddr;  //服务器地址

	//A.创建一个流式套接字
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	seraddr.sin_family = AF_INET;
	seraddr.sin_port = PORT;
	seraddr.sin_addr.s_addr = IPV4; 
	//B.向服务器地址发送连接
	r = connect(sockfd, (struct sockaddr*)&seraddr, sizeof(seraddr));
	if(r < 0){ perror("connect() error");	return -1;	}

	//C.通信
	pthread_create(&tid_info, NULL, pthread_info, &sockfd); // 采集中心线程
	pthread_create(&tid_ctl, NULL, pthread_ctl, &sockfd);   // 控制中心线程 

	pthread_join(tid_info, NULL);   //阻塞等待线程结束 
	pthread_join(tid_ctl, NULL);
	//D.关闭套接字
	close(sockfd);
	
	return 0;
}
