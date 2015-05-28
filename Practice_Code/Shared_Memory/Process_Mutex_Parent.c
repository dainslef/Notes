#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <sys/shm.h>				//包含共享内存的相关函数

int shm_id;							//共享内存标志，类似于文件标识符
pthread_mutexattr_t attr;

void dealSignal(int signal)
{
	if (signal == SIGQUIT
			&& !pthread_mutex_unlock((pthread_mutex_t*)shmat(shm_id, NULL, 0)))
	{
		printf("解锁互斥量成功！\n父进程即将结束！\n");
		for (int i = 5; i > 0; i--)
		{
			printf("倒数计时：%d\n", i);
			sleep(1);
		}
		printf("父进程结束！\n");
		_exit(0);
	}
}

int main(void)
{
	shm_id = shmget((key_t)666, sizeof(pthread_mutex_t), IPC_CREAT | 0600);
	pthread_mutex_t *mutex = (pthread_mutex_t*)shmat(shm_id, NULL, 0);

	pthread_mutexattr_init(&attr);				//初始化权限结构体attr
	pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
	
	if (!pthread_mutex_init(mutex, &attr))
		printf("成功创建了互斥量！\n");		//创建了一个进程互斥的互斥量

	signal(SIGQUIT, dealSignal);
	printf("父进程启动：\n");
	
	if (!pthread_mutex_lock((pthread_mutex_t*)shmat(shm_id, NULL, 0)))
		printf("父进程互斥量加锁成功！");
		
	while (1)
	{
		printf("父进程在执行！\n");
		sleep(2);
	}
	
	return 0;
}
