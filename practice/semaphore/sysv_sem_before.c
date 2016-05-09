/*
 * 代码完成时间： 2015-4-14 15：09 PM
 * XSI IPC Semaphore 信号量
 * 创建信号量，将信号量加锁后执行循环，直到接收到SIGINT信号后释放锁比并结束进程
 */

/**
 *
 * @author dainslef
 */

#include "sysv_sem.h"

void deal_signal(int sig)
{
	if (semop(sem_id, &sem_ok, 1) == -1)		//将信号量+1,释放资源
		perror("semop");
	else
		printf("信号量解锁成功！\n");

	_exit(0);
}

int main(void)
{
	sem_init();
	signal(SIGINT, deal_signal);

	sem_id = semget(ftok(PATH, PROJECT_ID), 1, IPC_CREAT | IPC_EXCL | 0600);
	if (sem_id == -1)
	{
		perror("semget");
		return 0;
	}
	else
		printf("信号量创建成功！\n");

	if (semctl(sem_id, 0, SETVAL, 1) == -1)		//初始化信号量时可以不自定义联合体直接赋值
		perror("semctl");

	if (semop(sem_id, &sem_wait, 1) == -1)		//信号量-1，锁住资源
		perror("semop");
	else
		printf("信号量加锁成功！\n");

	while (1)		//由于信号量被锁，因此A在执行此段代码时，B在等待
	{
		sleep(3);
		printf("正在执行\n");
	}

	return 0;
}
