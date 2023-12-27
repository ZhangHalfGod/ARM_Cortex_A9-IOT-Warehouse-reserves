#include "all.h"
//更新共享内存线程  
void *pthread_refresh(void *p)
{
	int shmid;
	key_t key = 666;
	envinfo_t  *shm_buf = NULL; 
	//A. 创建一个共享内存
	shmid = shmget(key, 300, IPC_CREAT|0666);
	if(shmid < 0){		perror("shmget() error");	pthread_exit(0);	}
	//B. 映射 
	shm_buf = shmat(shmid, NULL, 0);
	if(shm_buf == (void *)-1) { perror("shmdt() error");  pthread_exit(0);  }

	//envinfo_t a = {1, 23, 5, 40, 8, 20, 10, 0, 1800, 300, 3}; //临时测试
	while(1) {
		sem_wait(&SemEnv);	//信号量-3 P操作 : 睡眠 
	//	sleep(2);      //临时测试 
	//	a.temp[0]++;   //临时测试
	//	a.hum[0]--;    //临时测试
		//C. 将环境信息写入
		*shm_buf = Env;    //a;    //临时测试a 
		printf("%s : running...\n\n", __func__);
	}
	//D. 解除映射
	shmdt(shm_buf);
	//E. 删除共享内存
	//shmctl(shmid, IPC_RMID, NULL);
}
