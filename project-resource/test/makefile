#定义目标变量
EXEC = main

#依赖的文件
OBJS += student.o

#依赖的文件
OBJS += main.o

#定义变量存储编译器
CC = gcc

$(EXEC):$(OBJS)
	$(CC) -o $@ $^
	#$@ == main
	#$^ == student.o main.o
 
#隐式编译
.o:.c
	$(CC) -c $<