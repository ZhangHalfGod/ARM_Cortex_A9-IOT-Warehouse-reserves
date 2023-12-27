$(warning KERNELRELEASE=$(KERNELRELEASE))
ifeq ($(KERNELRELEASE),)

#KERNELDIR ?= /home/lht/kernel2.6/linux-2.6.14

KERNELDIR ?= /lib/modules/$(shell uname -r)/build  
PWD := $(shell pwd)

modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

#MAKE工程管理器
#make命名默认寻找第一个目标modules
#make -C就是指调用执行的路径
#$(KERNELDIR)Linux源码目录
#$(PWD)当前目录变量
#modules要执行的操作
#功能：到内核编译驱动代码生成ko文件复制到pwd标示的目录下面

modules_install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions Module* modules*

.PHONY: modules modules_install clean

else
    obj-m := hello.o
endif