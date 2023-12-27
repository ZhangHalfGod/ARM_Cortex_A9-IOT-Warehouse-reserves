/* 说明
 * 本文件的描述 ： IoT感知层使用的头文件
 * 版权 ：   华清远见
 * 版本号 ： 1.0
 * 作者 :    yuhang
 * 时间 ：2023-05-06
 * 历史记录 ：
 * 上一次版本号： 无
 * 上一次作者 ： 无
 * 上一次时间 ： 无
 * */
#ifndef   _ALL_H_
#define   _ALL_H_
//(1)  所有的头文件
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
//socket 头文件*5
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//随机数 头文件 
#include <time.h>

//(2)   所有的宏
#define IPV4  inet_addr("192.168.20.4")    //服务器的IP
#define PORT  htons(59999)              //服务器的端口号

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
#define SEGON   (DEVNO<<6 | SEG<<4 | 0)  //开数码管-0
#define SEGOFF  (DEVNO<<6 | SEG<<4 | 0xf) //关数码管 

//(3)   数据类型 
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

typedef struct goodsinfo  //货物结构体类型
{
	unsigned char type;   	//类型标志  'g'表示货物类型；否则,环境类型
	unsigned char devno;	//仓库号
	unsigned char inout;    //货物入库'I' or 出库'O'
	char name[17];			//货物名
	unsigned int num;		//货物数量 
}goods_t;


//(4)   函数声明
void *pthread_info(void *);    // 采集中心线程
void *pthread_ctl(void *);     // 控制中心线程

envinfo_t getEnv(void) ;       // 采集环境信息 
goods_t   getGoods(void);      // 采集货物信息 

void all_ctl(unsigned char);   // 控制设备功能

#endif

