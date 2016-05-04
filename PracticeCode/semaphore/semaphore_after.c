/*
 * 代码完成时间： 2015-4-14 15：09 PM
 * Unix IPC Semaphore 信号量
 * 获取信号量，等待信号量解锁，信号量解锁后执行循环，收到SIGINT信号之后删除信号量并结束进程
 */

/**
 *
 * @author dainslef
 */

#define PROJECT_ID 0
#define PATH "/home/dainslef"

#include <sys/sem.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int sem_id = 0;

void deal_signal(int sig)
{
	semctl(sem_id, 0, IPC_RMID);		//删除信号量
	_exit(0);
}

int main(void)
{
	signal(SIGINT, deal_signal);

	sem_id = semget(ftok(PATH, PROJECT_ID), 1, 0600);		//需要保证进程有读写信号量的权限
	if (sem_id == -1)
	{
		perror("semget");
		return 0;
	}
	else
		printf("信号量获取成功！\n");

	struct sembuf sem_wait;
	sem_wait.sem_num = 0;
	sem_wait.sem_op = -1;
	sem_wait.sem_flg = SEM_UNDO;

	semop(sem_id, &sem_wait, 1);

	while (1)
	{
		sleep(3);
		printf("正在执行\n");
	}

	return 0;
}