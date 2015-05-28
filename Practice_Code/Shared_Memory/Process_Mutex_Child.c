#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/shm.h>

int shm_id;
pthread_mutexattr_t attr;

int main(void)
{
	shm_id = shmget((key_t)666, sizeof(pthread_mutex_t), 0);
	pthread_mutex_t *mutex = (pthread_mutex_t*)shmat(shm_id, NULL, 0);

	pthread_mutexattr_init(&attr);
	pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
	
	printf("子进程启动：\n");
	
	if (!pthread_mutex_lock((pthread_mutex_t*)shmat(shm_id, NULL, 0)))
		printf("子进程互斥量加锁成功！");
		
	while (1)
	{
		printf("子进程在执行！\n");
		sleep(2);
	}
	
	return 0;
}
