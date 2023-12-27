//驱动的头文件
#include<linux/init.h>

#include<linux/module.h>
//驱动的初始化函数
int __init hello_init(void){
 //__init是驱动的初始化标识
 
 //输出内容 
 printk("call hello_init!\n");
 return 0;
}

//驱动的退出函数
int __exit hello_exit(void){
 //__exit 标识是结束函数
 //输出内容  
 printk("call hello_exit!\n");
 return 0;
}



//入口,入口标记：module_init
module_init(hello_init);

//出口,出口标记：module_exit
module_exit(hello_exit);

//需求：编译一下？