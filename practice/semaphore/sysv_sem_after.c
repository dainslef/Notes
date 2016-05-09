/*
 * 代码完成时间： 2015-4-14 15：09 PM
 * XSI IPC Semaphore 信号量
 * 获取信号量，等待信号量解锁，信号量解锁后执行循环，收到SIGINT信号之后删除信号量并结束进程
 */

/**
 *
 * @author dainslef
 */

#include "sysv_sem.h"

void deal_signal(int sig)
{
	if (semctl(sem_id, 0, IPC_RMID) == -1)		//删除信号量
		perror("semctl");
	else
		printf("信号量移除成功！\n");

	_exit(0);
}

int main(void)
{
	sem_init();
	signal(SIGINT, deal_signal);

	sem_id = semget(ftok(PATH, PROJECT_ID), 1, 0600);		//需要保证进程有读写信号量的权限
	if (sem_id == -1)
	{
		perror("semget");
		return 0;
	}
	else
		printf("信号量获取成功！\n等待信号量解锁。。。\n");



	if (semop(sem_id, &sem_wait, 1) == -1)
		perror("semop");
	else
		printf("信号量解锁成功！\n");

	while (1)
	{
		sleep(3);
		printf("正在执行\n");
	}

	return 0;
}
