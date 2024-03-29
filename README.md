# ARM_Cortex_A9-IOT-Warehouse-reserves
>基于ARM Cortex-A9的物联网仓储系统
>是一种基于物联网技术的智能化仓库管理系统，通过连接仓库内的各种设备和传感器，实现对仓储环境、货物位置、库存数量等信息的实时监测和控制，提高仓储物流效率和精度。
>该系统可以有效地降低仓库管理成本，提高货物处理效率，同时在保障货物安全方面也具有极大的优势。
<br>
# img src="https://github.com/ZhangHalfGod/Picture/blob/main/%E5%9B%BE%E7%89%87%202.png"  

## 本系统几个层次  
<img src="https://github.com/ZhangHalfGod/Picture/blob/main/%E5%9B%BE%E7%89%87%201.png">  

# 效果演示  

## 物联网仓储系统数据*回传功能*实现如下：  
<img src="https://github.com/ZhangHalfGod/Picture/blob/main/%E5%9B%BE%E7%89%87%203.png">  

>在环境信息中可以看到温度、湿度、光照、电量、电压等参数的变化

## 物联网仓储系统*远程控制功能*实现如下：
<img src="https://github.com/ZhangHalfGod/Picture/blob/main/%E5%9B%BE%E7%89%87%204.png">  

>通过M0版远程控制ARM开发板Led、Beep、Fan等设备的开关


## 开灯
<img src="https://github.com/ZhangHalfGod/Picture/blob/main/%E5%9B%BE%E7%89%87%205.png">  

>通过Led on按钮开启灯光

## 关灯
<img src="https://github.com/ZhangHalfGod/Picture/blob/main/%E5%9B%BE%E7%89%87%206.png">  

>通过Led off按钮关闭灯光


# 各模块功能实现  
## Sen和App发送接收测试实现代码：  
### 信息采集端代码pthread_info.c:
<img src="https://github.com/ZhangHalfGod/Picture/blob/main/%E5%9B%BE%E7%89%87%207.png">  

### 控制端代码pthread_ctl.c:
<img src="https://github.com/ZhangHalfGod/Picture/blob/main/%E5%9B%BE%E7%89%87%208.png">  

## Sen和App发送接收实现效果图：
<img src="https://github.com/ZhangHalfGod/Picture/blob/main/%E5%9B%BE%E7%89%87%209.png"> 


## 交叉编译功能实现  

>1.将gcc-4.6.4.tar.xz复制到/home/linux/，并解压成gcc-4.6.4文件

>2.pwd命令显示路径 /home/linux/yizhi/gcc-4.6.4/bin，通过命令sudo vim /etc/environment 追加：:/home/linux/yizhi/gcc-4.6.4/bin"

>3.激活：source /etc/environment arm-none-linux-gnueabi-gcc -v查看gcc版本

<img src="https://github.com/ZhangHalfGod/Picture/blob/main/%E5%9B%BE%E7%89%87%210.png"> 



>4.编辑Makefile:更新：CC=arm-none-linux-gnueabi-gcc

<img src="https://github.com/ZhangHalfGod/Picture/blob/main/%E5%9B%BE%E7%89%87%211.png">   

## 编写LED驱动

>LED_ON

<img src="https://github.com/ZhangHalfGod/Picture/blob/main/%E5%9B%BE%E7%89%87%212.png">   

>LED_OFF

<img src="https://github.com/ZhangHalfGod/Picture/blob/main/%E5%9B%BE%E7%89%87%213.png">  

## 交叉编译并下载  

>编译LED_ON

<img src="https://github.com/ZhangHalfGod/Picture/blob/main/%E5%9B%BE%E7%89%87%214.png">  


>编译LED_OFF

<img src="https://github.com/ZhangHalfGod/Picture/blob/main/%E5%9B%BE%E7%89%87%215.png">  

>1.启动a9， 配置网络：ifconfig eth0 192.168.20.5


>2.下载：tftp -g -r Sen-20.4-v2 192.168.20.3
 下载：tftp -g -r ledon 192.168.20.3
 下载：tftp -g -r ledoff 192.168.20.3
 下载：tftp -g -r hello.ko 192.168.20.3

>3.a9:  chmod 777 Sen-20.4-v2 
       chmod 777 ledon  
       chmod 777 ledoff  
       chmod 777 hello.ko

>4. a9:
       insmod hello.ko  
       rm /dev/led 
       rmmod fs4412_led
       mknod /dev/led c  254 0


## A9开发板、Linux网络配置：

>1.将VM虚拟机网络设置为桥接模式，然后在pc端启动两个vm网卡并在其属性中勾选VMware Bridge Protocol选项，最后将pc机以太网设置为静态IP：192.168.20.3

<img src="https://github.com/ZhangHalfGod/Picture/blob/main/%E5%9B%BE%E7%89%87%216.png">
<img src="https://github.com/ZhangHalfGod/Picture/blob/main/%E5%9B%BE%E7%89%87%217.png">

>2.设置Linux网卡IP 执行：sudo ifconfig eth0 192.168.20.4（该命令用于固定IP）

>3.设置A9的网卡IP：执行：sudo ifconfig eth0 192.168.20.5

>4.A9开发板端、Linux端和PC机互ping，查看网络是否畅通

<img src="https://github.com/ZhangHalfGod/Picture/blob/main/%E5%9B%BE%E7%89%87%218.png">
<img src="https://github.com/ZhangHalfGod/Picture/blob/main/%E5%9B%BE%E7%89%87%219.png">















