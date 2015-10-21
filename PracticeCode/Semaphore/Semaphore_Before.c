/*
 * 代码完成时间： 2015-4-14 15：09 PM
 * Unix IPC Semaphore 信号量
 * 创建信号量，将信号量加锁后执行循环，直到接收到SIGINT信号后释放锁比并结束进程
 */

/**
 *
 * @author dainslef
 */

#include <sys/sem.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int sem_id = 0;
struct sembuf sem_wait;
struct sembuf sem_ok;

void dealSignal(int sig)
{
	semop(sem_id, &sem_ok, 1);		//将信号量+1,释放资源
	_exit(0);
}

int main(void)
{
	signal(SIGINT, dealSignal);
	
	sem_id = semget(9999, 1, IPC_CREAT | IPC_EXCL | 0600);
	if (sem_id == -1)
	{
		printf("创建信号量失败！\n");
		return 0;
	}
	else
		printf("信号量创建成功！\n");
	
	sem_wait.sem_num = sem_ok.sem_num = 0;
	sem_wait.sem_op = -1;		//设置操作数，等待时-1
	sem_ok.sem_op = 1;			//等待完毕+1
	sem_wait.sem_flg = sem_ok.sem_flg = SEM_UNDO;
	semctl(sem_id, 0, SETVAL, 1);		//初始化信号量时可以不自定义联合体直接赋值。此外，只有创建信号量的进程才需要初始化信号量，获取信号量的进程不需要
	semop(sem_id, &sem_wait, 1);	//信号量-1，锁住资源

	while (1)		//由于信号量被锁，因此A在执行此段代码时，B在等待
	{
		sleep(3);
		printf("正在执行\n");
	}
	
	return 0;
}
