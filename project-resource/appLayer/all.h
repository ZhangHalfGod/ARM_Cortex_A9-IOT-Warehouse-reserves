/* 说明
 * 本文件的描述 ： IoT应用层使用的头文件
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
#include <sys/ipc.h>   // 共享内存头文件*2
#include <sys/shm.h>   
#include <sys/msg.h>   // 消息队列头文件*2  ipc.h  msg.h
//socket 头文件*5
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <semaphore.h>    //线程-信号量的头文件 
#include <sqlite3.h>      //数据库头文件 

//(2)   所有的宏
#define IPV4  inet_addr("192.168.20.4")    //服务器的IP
#define PORT  htons(59999)              //服务器的端口号
//(3)   数据类型
struct msg{
	long type;    //消息队列：过滤的类型
	long msgtype; //消息队列: 正文-1  类型 
	unsigned char text[32]; //正文-2 数据内容
};

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

typedef union{   //共用体/联合体  成员共用同一个存储空间.每次只存储其中一个成员
	envinfo_t  env;   //环境 
	goods_t    goods; //货物 
}data_t;	  //数据域的数据类型 
//链表(中节点)的数据类型定义
typedef struct node{
	data_t data;  		//数据域 
	struct node *next;  //指针域
}linknode_t, *linklist_t;
//(4)   函数声明
linknode_t *createLink(void);   //创建空链表
int isEmpty(linknode_t *);      //判断链表是否空
int insertLinkEnd(linknode_t *, data_t );   //在链表表尾插入
int deleteLinkHead(linknode_t *, data_t *);  //从链表表头删除 ,获得数据值
void freeLink(linknode_t *);    //释放链表

void *pthread_transfer(void *);    // 接收M0数据线程
void *pthread_analysis(void *);     // 分析数据线程
void *pthread_refresh(void *);      // 更新共享内存线程
void *pthread_sqlite(void *);       // 数据库操作线程
void *pthread_sms(void *);    		// 短信报警线程
void *pthread_client_request(void *); // 处理消息队列线程
void *pthread_uart_cmd(void *);     // 向M0发送命令线程

int sqliteGoods(goods_t *);   //数据库总算法实现函数
int insertGoods(sqlite3 *, goods_t *);   //执行SQL插入货物
int deleteGoods(sqlite3 *, goods_t *);    //执行SQL删除货物
int updateGoods(sqlite3 *, goods_t *, int);  //执行SQL更新货物
int selectGoodsNum(sqlite3 *, goods_t *, int *); //执行SQL查货物数量 
int createTables(void);  // 执行SQL创建仓库相关表格


// 外部引用全局变量声明 
extern pthread_mutex_t  MutexLink;  	// 互斥锁-1  互斥的链表
extern pthread_cond_t   CondCmd;    	// 条件变量-1 控制命令的条件变量 
extern pthread_mutex_t  MutexCmd;   	// 同条件变量一起使用的互斥锁 
extern sem_t SemEnv, SemGoods, SemSms;  // 信号量-1 环境的信号量、货物的信号量、异常信号量

extern unsigned char CtlCmd;            // 控制命令全局变量
extern envinfo_t     Env;				// 环境数据
extern goods_t       Goods;             // 货物数据 

extern linknode_t   *Link;				// 链表指针

#endif
