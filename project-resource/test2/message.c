#include<stdio.h>
#include<sys/msg.h>


//消息结构体类型
struct msg{
//类型随意
long mtype;
char mtext[100];

};



int main(){

//获得创建消息队列的唯一幻数
int key = ftok("/temp",2);
//key幻数
//“/temp”参数1，有意义的文件夹
//2，是生成的幻数
//定义变量存储消息队列的id
int msgid2=0;
//创建消息队列
msgid2=msgget(key   ,   0666 |IPC_CREAT);
printf("消息队列的id是:%d\n",msgid2);

//定义消息
struct msg s={1,   "hello world" };


//发送消息
msgsnd(msgid2,  &s   ,   100  ,    0);
//     标识    消息类型    正文大小  阻塞等待（满等待）
printf("发送成功\n");

return 0;

}