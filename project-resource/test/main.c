//使用头文件： 
//当前目录下： 不是系统的头文件
#include"student.h"

//系统的基本的头文件
#include<stdio.h>

//添加free的支持
#include<stdlib.h>

//定义宏
#define SAFE_FREE(p) do{free(p);p = NULL;}while(0);
      //语句1;语句2;


//入口方法
int main()
{
 //数字存储：随机的，自己的
 int a[7] = { 0 }, b[7] = { 0 }, c = 0;
 int i, j;
 //随机种子
 srand(time(0));
 //产生7个随机数
 for(i = 0; i < 7; i++)
 {
  //产生随机数码给元素赋值操作
  a[i] = rand() % 35 + 1; 
  for(j = 0; j < i; j++)
  {
   //判断重复
   if(a[i] == a[j])
   {
    i--; //有一个相等的，重出
    break; //因为有相等的，就结束这个for循环
   }
  } 
 }
 //用户输入号码给数组b存储
 scanf("%d%d%d%d%d%d%d", &b[0], &b[1], &b[2], &b[3], &b[4], &b[5], &b[6]);
 printf("rand %d,%d,%d,%d,%d,%d,%d\n", a[0], a[1], a[2], a[3], a[4], a[5], a[6]); 
 for(i = 0; i < 7; i++)//随机的号码
 {
  for(j = 0; j < 7; j++)//自定义的号码
  {
   if(a[i] == b[j])//相等了
   {
    c++;//统计！
    break; //因为有一个相等，后面的不比较
   }
  }
 }
 switch(c)
 {
 case 7: printf("500 wan\n");   break;
 case 6: printf("100 wan\n");   break;
 case 5: printf("1 wan\n");   break;
 case 4: printf("5000\n");   break;
 case 3: printf("500\n");   break;
 default: printf("sorry again\n"); break;
 }
}