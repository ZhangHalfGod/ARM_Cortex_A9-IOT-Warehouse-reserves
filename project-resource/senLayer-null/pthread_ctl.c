#include "all.h"
//控制中心线程
void *pthread_ctl(void *p)
{
		//参数是标识，通信的标识
		int fd = *((int *)p);
		//接收的命令存储在cmd
		unsigned char cmd;
		//一直接收
		while(1){
			//接收数据，网页 发送命令 给应用程序， 应用程序控制外设
			recv(fd, &cmd, sizeof(cmd), 0);
			//参数1：通信标识符号
			//参数2：发送的命令存储的位置（地址）
			//参数3：发送的命令的大小
			//参数4：默认的（阻塞的）
			//控制函数
			all_ctl(cmd);
			//cmd发送的命令
		}
		
		
}
/*
#define DEVNO 1  //仓库号
#define FAN  0    //设备号*4
#define BEEP 1
#define LED  2
#define SEG  3
#define FANOFF 	(DEVNO<<6 | FAN<<4 | 0)  //关风扇的命令
#define FANON1  (DEVNO<<6 | FAN<<4 | 1)  //开风扇1档
#define FANON2  (DEVNO<<6 | FAN<<4 | 2)  //开风扇2档
#define FANON3  (DEVNO<<6 | FAN<<4 | 3)  //开风扇3档
#define BEEPOFF (DEVNO<<6 | BEEP<<4 | 0) //关蜂鸣器
#define BEEPON  (DEVNO<<6 | BEEP<<4 | 1) //开蜂鸣器
#define LEDOFF  (DEVNO<<6 | LED<<4 | 0)  //关灯
#define LEDON   (DEVNO<<6 | LED<<4 | 1)  //开灯
*/
//自定义函数:控制设备开关
void all_ctl(unsigned char cmd)
{
	//参数1：操作码
	//操作命令
	switch(cmd){
		case FANOFF:
			//输出内容 
			printf("fan off ******\n");
			//退出分支
			break;
		case FANON1:
			//输出内容 
			printf("fan on1 ******\n");
			//退出分支
			break;
		case FANON2:
			//输出内容 
			printf("fan on2 ******\n");
			//退出分支
			break;
		case FANON3:
			//输出内容 
			printf("fan on3 ******\n");
			//退出分支
			break;
		case BEEPOFF:
			//输出内容 
			printf("Beep off ******\n");
			//退出分支
			break;
		case BEEPON:
			//输出内容 
			printf("Beep on ******\n");
			//退出分支
			break;
		case LEDOFF:
			//输出内容 
			printf("led off ******\n");
			//退出分支
			system("/ledoff");
			break;
		case LEDON:
			//输出内容 
			printf("led on ******\n");
			//退出分支
			system("/ledon");
			break;
	}


}
