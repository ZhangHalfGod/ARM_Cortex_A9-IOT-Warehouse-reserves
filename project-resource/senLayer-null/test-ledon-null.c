#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
struct buf
{
	int led_num;   //led 编号
	int led_state;  //设置的状态
};
//让灯闪烁
int main()
{
	struct buf data;
 //   mknod   /dev/led   c   254   0
 int fd = open("/dev/led", O_RDWR);
 if(fd < 0){
  printf("file open error\n");
 }
 
  data.led_num = 4;
  data.led_state = 1;
  write(fd, &data, sizeof(data));
  close(fd);
 return 0; 

}
