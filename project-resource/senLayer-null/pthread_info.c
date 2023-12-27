#include "all.h"
//采集中心线程
//线程的工作：线程处理函数：
void *pthread_info(void *p)
{
	//p指向通信的标识
	//*p是通信的标识
	//*p是标识，是数
	int fd = *((int *)p);
	//fd是通信的标识，fd标识一个通信的 标记
	
	//模拟随机的内容，需要播种 srand()
	srand(time(0));//种子
	
	//不断发消息
	while(1){
		//获得结构体内容
		envinfo_t env = getEnv();

		//给物联网服务器发消息
		send(fd, &env, sizeof(env), 0);
		
		//输出发送的消息
		printf("id:%d %d.%d %d.%d %d %d %d %d %d %d\n", env.devno, env.temp[0], env.temp[1], env.hum[0], env.hum[1], env.x, env.y, env.z, env.light, env.electricity, env.voltage);
		
		//延迟
		sleep(1);
	}
	

	pthread_exit(0);
}

//自定义函数：采集环境信息 
//底层硬件：信息发送
/*
typedef struct envinfo //环境结构体类型
{
	unsigned char devno;   	//仓库号
	unsigned char temp[2]; 	//温度
	unsigned char hum[2];	//湿度
	signed char x, y, z;	//三轴加速度xyz
	signed int light;     //光照强度
	signed int electricity; //电量
	signed int voltage;     //模拟电压
}envinfo_t;

*/
envinfo_t getEnv(void)
{
	//自定义消息报文结构体变量
	envinfo_t a;
	
	a.devno = DEVNO;
	
	a.temp[0] = rand() % 50;
	
	a.temp[1] = rand() % 10;
	
	a.hum[0] = rand() % 50;
	
	a.hum[1] = rand() % 10;
	
	a.x = rand() % 256 - 128;
	
	a.y = rand() % 256 - 128;
	
	a.z = rand() % 256 - 128;
	
	a.light = rand() % 1000;
	
	a.electricity = rand() % 1000;
	
	a.voltage = rand() % 6;
	
	
	return a;
}
