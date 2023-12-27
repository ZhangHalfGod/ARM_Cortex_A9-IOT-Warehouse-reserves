#编译器变量
CC=arm-none-linux-gnueabi-gcc
#相关链接的库
AFLAGS:=-lpthread  
#依赖文件
OBJS=main.o pthread_info.o pthread_ctl.o
#最终的可执行文件名字
EXE=Sen

#执行make, 到这里执行下面的
$(EXE) : $(OBJS) 
	$(CC)  $^  $(AFLAGS) -o $@
#执行make clean （删除）
clean:
	rm *.o $(EXE) 
#执行make rebuild（重新编译=删除+编译）
rebuild:clean $(EXE)
