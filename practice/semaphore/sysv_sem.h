#define PROJECT_ID 0
#define PATH "/home/dainslef"

#include <sys/sem.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int sem_id = 0;
struct sembuf sem_wait;
struct sembuf sem_ok;

void sem_init()
{
	sem_wait.sem_num = sem_ok.sem_num = 0;
	sem_wait.sem_op = -1;		//设置操作数，等待时-1
	sem_ok.sem_op = 1;			//等待完毕+1
	sem_wait.sem_flg = sem_ok.sem_flg = SEM_UNDO;
}